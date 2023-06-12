#include "request.h"
#include <QString>
Request::Request()
{

}

int cnt;
struct contest{
    std::string id,name,type,phase,frozen;
    std::string durationSeconds,startTimeSeconds,relativeTimeSeconds;
}a[20];
std::map<int,std::string>p;

void coming(contest c){
    long long starttime=stol(c.startTimeSeconds);
    time_t timestamp=starttime;
    struct tm *timeinfo;

    // 转换为时间结构
    timeinfo = gmtime(&timestamp);

    // 调整时区为UTC+8
    timeinfo->tm_hour += 8;
    mktime(timeinfo);
  QString do_text(c.name.c_str());
  char buffer[80];
  strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
  QString ti = QString::fromUtf8(buffer);
  QSqlQuery q;
  q.prepare("INSERT INTO \"do-thing\" (things, Time) VALUES ('"+do_text+"','"+ ti+"')");
  q.exec();

}


size_t writeCallback(char* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append(contents, totalSize);
    return totalSize;
}


void cal(std::string s){
    p[0]="id",p[1]="name";
    p[2]="type",p[3]="phase";
    p[4]="frozen",p[5]="durationSeconds";
    p[6]="startTimeSeconds",p[7]="relativeTimeSeconds";

    int len=s.size();
    for (int l = 0; l < len; l++) {
        if(s[l]!='{')continue;

        std::string t = "";
        if (s[l] == '{') {
            int r = l;
            while (r < len and s[r] != '}') {
                t += s[r];
                r++;
            }
            l=r;
        }
        //        qDebug() << t;


        int now = 0;
        ++cnt;
        for (int j = 0; j < t.size() and now < 8; j++) {
            if (t.substr(j, p[now].size()) == p[now]) {
                std::string res = "";
                int L = j + p[now].size() + 2;
                int R = L + 1;
                while (R < t.size() and t[R] != '"') {
                    R++;
                }
                for (int k = L; k <= R - 1; k++) {
                    if (t[k] != '"' and t[k] != ',' and t[k] != ':' and t[k]!='\\') res += t[k];
                }
                //                qDebug()<<res;
                if (now == 0)
                    a[cnt].id = res;
                else if (now == 1)
                    a[cnt].name = res;
                else if (now == 2)
                    a[cnt].type = res;
                else if (now == 3)
                    a[cnt].phase = res;
                else if (now == 4)
                    a[cnt].frozen = res;
                else if (now == 5)
                    a[cnt].durationSeconds = res;
                else if (now == 6)
                    a[cnt].startTimeSeconds = res;
                else if (now == 7)
                    a[cnt].relativeTimeSeconds = res;
                now++;
            }
        }
        if(a[cnt].phase!="BEFORE"){
            //            qDebug()<<a[cnt].phase;
            break;
        }
        //        else qDebug()<<t;
    }
    //    qDebug()<<cnt;
    for(int j=1;j<=cnt;j++){
        //        pr(j);
        coming(a[j]);
    }
}

void Request::run()
{
    CURL* curl = curl_easy_init();
    if (curl) {
        // 设置请求的 URL
        curl_easy_setopt(curl, CURLOPT_URL, "https://codeforces.com/api/contest.list?gym=false");

        // 设置回调函数，用于接收响应数据
        std::string response;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        //        curl_easy_setopt(curl, CURLOPT_CAINFO, "C:/libcurl/bincurl-ca-bundle.crt");

        // 发送请求
        CURLcode result = curl_easy_perform(curl);
        if (result == CURLE_OK) {
            // 请求成功，处理响应数据
            // 在 response 变量中获取响应数据
            std::string qs(response.c_str());
            //            qDebug() << qs;
            cal(qs);
            //            qDebug() << "Response: " << response.c_str();
        } else {
            // 请求失败，输出错误信息
            qDebug() << "cURL request failed: " << curl_easy_strerror(result);
        }

        // 清理 cURL 资源
        curl_easy_cleanup(curl);
    }
}
