#ifndef MEMO_H
#define MEMO_H

#include <QMainWindow>
#include <QWidget>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>

class QtMaterialAppBar;
namespace Ui {
class memo;
}

class memo : public QMainWindow
{
    Q_OBJECT

public:
    explicit memo(QWidget *parent = nullptr);
    ~memo();

private:
    Ui::memo *ui;
    QtMaterialAppBar * appBar ;
};

#endif // MEMO_H
