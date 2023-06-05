#ifndef MEMO_H
#define MEMO_H

#include <QMainWindow>
#include <QWidget>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QDebug>
class QtMaterialAppBar;
class QtMaterialDrawer;
class QtMaterialFloatingActionButton;

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
private:
    Ui::memo *ui;
    QColor a1;
    QColor a2;
    QColor a3;
    QColor a4;
    QColor ztys;
    QtMaterialAppBar                    * appBar   ;
    QtMaterialDrawer                    * drawer   ;
    QtMaterialFloatingActionButton      * act_but  ;

};

#endif // MEMO_H
