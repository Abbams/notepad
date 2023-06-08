#include "data_time.h"
#include <chrono>
#include <ctime>
QString data_time::putinf()
{

    QString res;
    res+=QString(std::to_string(hour).c_str());
    res+=':';
    res+=QString( std::to_string(minutes).c_str());
    res+=':';
    res+=QString( std::to_string(second).c_str());
    res+='\n';
    res+=QString( digitsMap[week]);
    res+='\n';
    res+=QString( std::to_string(month).c_str());
    res+='/';
    res+=QString( std::to_string(day).c_str());

    second+=1;
    if(second==60)
        second=0,minutes+=1;
    if(minutes==60)
        minutes=0,hour+=1;
    if(hour==24)
        hour=0,day+=1;

    return res;

}

data_time::data_time()
{
    auto now = std::chrono::system_clock::now();
       // 将时间点转换为 time_t
       std::time_t time = std::chrono::system_clock::to_time_t(now);

       // 将 time_t 转换为本地时间的 tm 结构
       std::tm* localTime = std::localtime(&time);

       // 从 tm 结构中获取时分秒
       second=localTime->tm_sec;
       year =localTime->tm_year;
       month =localTime->tm_isdst;
       day = localTime->tm_mday;
       hour = localTime->tm_hour;
       minutes = localTime->tm_min;
       week=localTime->tm_wday;
        month=localTime->tm_mon+1;
           digitsMap[1]= "星期一";
           digitsMap[2]= "星期二";
           digitsMap[3]= "星期三";
           digitsMap[4]= "星期四";
           digitsMap[5]= "星期五";
           digitsMap[6]= "星期六";
           digitsMap[7]= "星期日";


}
