#ifndef REQUEST_H
#define REQUEST_H
#include <QDebug>
#include <cstring>
#include <curl/curl.h>
#include <map>
#include <iomanip>
#include <ctime>
#include <iostream>
#include <QSqlQuery>
class Request
{
public:
    Request();
    void run();
};

#endif // REQUEST_H
