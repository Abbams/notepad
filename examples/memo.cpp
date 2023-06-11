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
#include <QDate>
#include <qtmaterialtextfield.h>
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

    request.Run();

}

memo::~memo()
{
    data_base.close();
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


    mydialog=new QtMaterialDialog;
    mydialog->setParent(this);

    QWidget *dialogWidget = new QWidget;
    QVBoxLayout *dialogWidgetLayout = new QVBoxLayout;
    dialogWidget->setLayout(dialogWidgetLayout);

    QtMaterialFlatButton *closeButton = new QtMaterialFlatButton("Close");
    QtMaterialFlatButton *submitbutton = new QtMaterialFlatButton("Submit");
    dialogWidgetLayout->addWidget(closeButton);
    dialogWidgetLayout->addWidget(submitbutton);
    dialogWidgetLayout->setAlignment(closeButton, Qt::AlignBottom | Qt::AlignCenter);
//    dialogWidgetLayout->setAlignment(submitbutton, Qt::AlignBottom | Qt::AlignCenter);
    closeButton->setMaximumWidth(300);
    QVBoxLayout *dialogLayout = new QVBoxLayout;
    mydialog->setWindowLayout(dialogLayout);
    QWidget *textQWidget=new QWidget;
    QVBoxLayout *layout = new QVBoxLayout();

        // 创建事件文本框
        eventTextField = new QtMaterialTextField;
        eventTextField->setLabel("事件");
        eventTextField->setUseThemeColors(true);
        layout->addWidget(eventTextField);

        // 创建时间文本框
        timeTextField = new QtMaterialTextField;
        timeTextField->setLabel("时间");
        timeTextField->setPlaceholderText("年-月-日 时:分:秒");
        timeTextField->setUseThemeColors(true);
        layout->addWidget(timeTextField);
        textQWidget->setLayout(layout);
    dialogWidget->setMinimumHeight(300);
    dialogLayout->addWidget(textQWidget);
    dialogLayout->addWidget(dialogWidget);
    connect(closeButton, &QtMaterialFlatButton::pressed,[&](){
    //新加待办事件
        eventTextField->clear();
        timeTextField->clear();
        mydialog->hideDialog();


    });
    connect(submitbutton, &QtMaterialFlatButton::pressed,[&](){
    //新加待办事件
        QString do_text = eventTextField->text();
        QString ti = timeTextField->text();
        qDebug()<<"INSERT INTO \"do-thing\" (things, Time) VALUES ('"+do_text+"','"+ ti+"')";
        QDateTime dateTime = QDateTime::fromString(ti, "yyyy-MM-dd HH:mm:ss");

        QSqlQuery q;
        q.prepare("INSERT INTO \"do-thing\" (things, Time) VALUES ('"+do_text+"','"+ ti+"')");


        if (q.exec()) {
            qDebug() << "Insertion successful";
        } else {
            qDebug() << "Insertion failed:" << q.lastError().text();
        }
        eventTextField->clear();
        timeTextField->clear();
        listmod->setQuery("select * from 'do-thing' WHERE finsh==0 ORDER BY Time DESC;");
        ui->listView->update();
        mydialog->hideDialog();

    });
    connect(act_but,&QtMaterialRaisedButton::pressed,[&](){

       mydialog->showDialog();
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
    listmod->setQuery("select * from 'do-thing' WHERE finsh==0 ORDER BY Time DESC;") ;
    ui->listView->setModel(listmod);
    ui->listView->setModelColumn(2);
    ui->listView->update();
}
