#include "memo.h"
#include "ui_memo.h"
#include <QtWidgets/QVBoxLayout>
#include <QColorDialog>
#include <qtmaterialappbar.h>
#include <QVBoxLayout>
#include <qtmaterialiconbutton.h>
#include <qtmaterialavatar.h>
#include <lib/qtmaterialtheme.h>
#include <qtmaterialdrawer.h>
#include <QLabel>
#include <qtmaterialflatbutton.h>
#include <qtmaterialfab.h>
#include <data_time.h>
memo::memo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::memo)
{
    ui->setupUi(this);
    open_database();
    appBar=new QtMaterialAppBar(ui->widget_appbar);
    drawer=new QtMaterialDrawer(ui->widget);
    ztys=QColor(170, 119, 255);
    a1=QColor(170, 119, 255);
    a2=QColor(170, 119, 255);
    a3=QColor(1,1,1);
    a4=QColor(110,231,214);
    init_appbar();
    init_actnut();
    this->setContentsMargins(0, 0, 0, 0);
    QTimer *ti=new QTimer;
    connect(ti,&QTimer::timeout,[&](){

        ui->label->setText(data_time::getInstance().putinf());
    });
    ti->start(1000);



}

memo::~memo()
{
    delete ui;
}

void memo::init_appbar()
{
    //文字
    QLabel *label = new QLabel("menu");
    label->setAttribute(Qt::WA_TranslucentBackground);
    label->setForegroundRole(QPalette::Foreground);
    label->setContentsMargins(0, 0, 0, 0);
    //画笔
    QPalette palette = label->palette();
    palette.setColor(label->foregroundRole(), a1);
    label->setPalette(palette);
    label->setFont(QFont("Roboto", 20, QFont::Normal));
    //按键
    QtMaterialIconButton *button = new QtMaterialIconButton(QtMaterialTheme::icon("navigation", "menu"));
    button->setColor(a3);
    button->setFixedWidth(50);
    button->setIconSize(QSize(25, 25));
    //用户头像
    QtMaterialAvatar * use_img=new QtMaterialAvatar();
//    use_img->setParent(this);
    use_img->setImage(QImage(":/images/assets/sikh.jpg"));
    use_img->setSize(33);

    init_drawer();
    //添加组件
    appBar->setBackgroundColor(a1);
    appBar->appBarLayout()->addWidget(button);
    appBar->appBarLayout()->addWidget(label,2);
    appBar->appBarLayout()->addWidget(use_img);
    appBar->setParent(ui->widget_appbar);
    appBar->setFixedSize({800,50});
    connect(button,&QtMaterialIconButton::pressed,[&](){

        drawer->openDrawer();

    });
    appBar->show();
}

void memo::init_drawer()
{

    QVBoxLayout *drawerLayout = new QVBoxLayout;
    drawer->setDrawerLayout(drawerLayout);
    QVector<QString> labels={"设置","待办"};
    QVector<QString>::iterator it;
    for (it = labels.begin(); it != labels.end(); ++it) {
         QtMaterialFlatButton* label = new QtMaterialFlatButton(*it);
        label->setBackgroundColor(a3);

        label->setMaximumHeight(30);
        label->setFont(QFont("Roboto", 10, QFont::Medium));
        drawer->drawerLayout()->addWidget(label);

    }
    drawer->setClickOutsideToClose(true);
    drawer->setOverlayMode(true);
    drawerLayout->setAlignment(Qt::AlignTop);
}

void memo::init_actnut()
{
    act_but=new QtMaterialFloatingActionButton(QtMaterialTheme::icon("toggle", "star"));
    act_but->setMini(1);
    connect(act_but,&QtMaterialRaisedButton::pressed,[](){

    });
    act_but->setParent(ui->widget_2);
}

void memo::open_database()
{
    data_base = QSqlDatabase::database("qt_sql_default_connection");
  data_base = QSqlDatabase::addDatabase("QSQLITE");
    data_base.setDatabaseName("MEMO_data.db");
    data_base.setUserName("data");
    data_base.setPassword("123456");

    if (!data_base.open())
    {
        qDebug() << "Error: Failed to connect database." << data_base.lastError();
    }
    listmod=new  QSqlQueryModel();
    listmod->setQuery("select * from 'do-thing'") ;
    ui->listView->setModel(listmod);
    ui->listView->setModelColumn(2);
    ui->listView->update();
}
