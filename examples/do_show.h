#ifndef DO_SHOW_H
#define DO_SHOW_H

#include <QWidget>

namespace Ui {
class do_show;
}

class do_show : public QWidget
{
    Q_OBJECT

public:
    explicit do_show(QWidget *parent = nullptr);
    ~do_show();

private:
    Ui::do_show *ui;
};

#endif // DO_SHOW_H
