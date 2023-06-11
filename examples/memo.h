#ifndef MEMO_H
#define MEMO_H

#include <QMainWindow>
#include <QWidget>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QStandardItemModel>
#include <QSqlTableModel>
#include <QSqlError>
#include <QTimer>
#include <qtmaterialdialog.h>
#include <qtmaterialflatbutton.h>
#include <request.h>
class QtMaterialAppBar;
class QtMaterialDrawer;
class QtMaterialFloatingActionButton;
class QtMaterialDialog;
class QtMaterialTextField;
namespace Ui {
class memo;
}

class memo : public QMainWindow
{
    Q_OBJECT

public:
    explicit memo(QWidget *parent = nullptr);
    ~memo();
    void init_appbar();
    void init_drawer();
    void init_actnut();
    void open_database();
private:
    Ui::memo *ui;
    QColor a1;
    QColor a2;
    QColor a3;
    QColor a4;
    QColor ztys;
    QSqlDatabase data_base;
    QSqlQueryModel *listmod;
    QtMaterialAppBar                    * appBar   ;
    QtMaterialDrawer                    * drawer   ;
    QtMaterialFloatingActionButton      * act_but  ;
    QtMaterialDialog                    * mydialog ;
    QtMaterialTextField                 *timeTextField;
    QtMaterialTextField                 *eventTextField;
    Request                             request;
};

#endif // MEMO_H
