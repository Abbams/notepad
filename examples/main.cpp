#include <QtWidgets/QApplication>
#include <QDebug>
#include "memo.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Q_INIT_RESOURCE(resources);
    memo window;
    window.show();

    return a.exec();
}
