#ifndef REQUEST_H
#define REQUEST_H
#include <QDebug>
#include <cstring>
#include <curl/curl.h>
#include <map>
#include <iomanip>
#include <ctime>
#include <iostream>

class Request
{
public:
    Request();
    void Run();
};

#endif // REQUEST_H
