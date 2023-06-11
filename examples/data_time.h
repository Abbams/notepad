#ifndef DATA_TIME_H
#define DATA_TIME_H
#include <QString>
#include <map>
class to_do_event;
class data_time
{
    public:
    static data_time& getInstance() {
        static data_time instance;
        return instance;
    }
    QString putinf();
    QString data();
    bool running_ = false;
private:

    data_time();
    data_time(const data_time&) = delete;
    data_time& operator=(const data_time&) = delete;
    std::map<int,QString> digitsMap ;
    int week;
    int year;
    int month;
    int day;
    int hour;
    int minutes;
    int second;
    QString ti_data;
};

#endif // DATA_TIME_H
