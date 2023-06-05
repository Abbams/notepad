#ifndef DATA_TIME_H
#define DATA_TIME_H

class to_do_event;
class data_time
{
    public:
    static data_time& getInstance() {
        static data_time instance;
        return instance;
    }

private:

    data_time();
    data_time(const data_time&) = delete;
    data_time& operator=(const data_time&) = delete;
    bool running_ = false;

    int year;
    int month;
    int day;
    int hour;
    int minutes;
};

#endif // DATA_TIME_H
