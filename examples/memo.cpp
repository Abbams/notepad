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
#include <qtmaterialsnackbar.h>
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
    //初始化顶部任务栏
    init_appbar();
    //初始化新加按键与弹出框
    init_actnut();

    this->setContentsMargins(0, 0, 0, 0);
    //设置时钟更新，1秒钟更新一次
    QTimer *ti=new QTimer;
    connect(ti,&QTimer::timeout,[&](){

        //直接调用时钟类的输出函数
        ui->label->setText(data_time::getInstance().putinf());
        //检测并没有精确到秒，而是分钟
        if(data_time::getInstance().running_==true)
        {

            data_time::getInstance().running_=false;
            determine();
        }
    });
    ti->start(1000);
    //链接列表点击与右信息栏更新函数
    connect(ui->listView,&QListView::clicked,this,&memo::chang_indix);
    //完成任务按键
    QtMaterialFlatButton* finish = new QtMaterialFlatButton("完成");

    //美化按键
    finish->setParent(ui->widget_2);
    finish->move({20,470});
    finish->setUseThemeColors(false);
    finish->setBackgroundColor(a1);
    finish->setTextAlignment(Qt::AlignLeft);
    finish->setForegroundColor(QColorConstants::White);
    finish->setFont(ui->do_thing->font());
    finish->setDisabled(false);

    //链接按键点击与数据库更新 ————当点击完成就把当前选择项的完成标志设置1
    connect(finish,&QtMaterialFlatButton::pressed,[&](){
        //找到当前选择项的索引
        QModelIndex currentIndex =ui->listView->currentIndex();
        if(currentIndex.isValid()==false)
            return;
        int row = currentIndex.row();
        //更新 名字等于当前事件名字，时间等于当前事件时间的finsh为1
        data_base.exec("UPDATE 'do-thing' SET finsh = 1 WHERE things='"+  listmod->data(ui->listView->currentIndex()).toString()\
                       +"' AND Time ='"+ listmod->data(ui->listView->currentIndex().siblingAtColumn(1)).toString()+"';");
        if (row < listmod->rowCount()) {
                // 如果还有下一个项，则选择下一个项
                ui->listView->setCurrentIndex(listmod->index(row+1, 2));
            } else if (row > 0) {
                // 如果没有下一个项但有上一个项，则选择上一个项
                ui->listView->setCurrentIndex(listmod->index(row - 1, 2));
            }
        //清除数据
        ui->do_thing->clear();
        ui->do_time->clear();
        //重新加载数据库和listview
        reload();
    });

}

memo::~memo()
{
    data_base.close();
    delete ui;
}

void memo::init_appbar()
{
    //该函数就只是创建与美化
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
    //初始化侧边弹出栏
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
    //该函数就只是创建与美化
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
    //新增一个按键，手动更新比赛信息
    QtMaterialFlatButton* label = new QtMaterialFlatButton("更新cf比赛");
   label->setBackgroundColor(a3);
   label->setMaximumHeight(30);
   label->setFont(QFont("Roboto", 10, QFont::Medium));
   drawer->drawerLayout()->addWidget(label);
    connect(label,&QtMaterialFlatButton::pressed,this,&memo::updata_codeforce);
    drawer->setClickOutsideToClose(true);
    drawer->setOverlayMode(true);
    drawerLayout->setAlignment(Qt::AlignTop);
}

void memo::init_actnut()
{
    //初始化新加按键与弹出框
    act_but=new QtMaterialFloatingActionButton(QtMaterialTheme::icon("toggle", "star"));
    act_but->setMini(1);
    m_snackbar=new QtMaterialSnackbar(this);
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
            //初始化面板
            eventTextField->clear();
            timeTextField->clear();
            mydialog->hideDialog();


        });
    connect(submitbutton, &QtMaterialFlatButton::pressed,[&](){
        //新加待办事件
        QString do_text = eventTextField->text();
        QString ti = timeTextField->text();
        QSqlQuery q;
        q.prepare("INSERT INTO \"do-thing\" (things, Time) VALUES ('"+do_text+"','"+ ti+"')");
        q.exec();
        //初始化面板
        eventTextField->clear();
        timeTextField->clear();
        reload();
        mydialog->hideDialog();

    });
    connect(act_but,&QtMaterialRaisedButton::pressed,[&](){
        timeTextField->setText(data_time::getInstance().data());
       mydialog->showDialog();
    });
    act_but->setParent(ui->widget_2);
}

void memo::open_database()
{
    //数据库链接
    data_base = QSqlDatabase::database("qt_sql_default_connection");
  data_base = QSqlDatabase::addDatabase("QSQLITE");
    data_base.setDatabaseName("MEMO_data.db");
    data_base.setUserName("data");
    data_base.setPassword("123456");

    if (!data_base.open())
    {
        qDebug() << "Error: Failed to connect database." << data_base.lastError();
    }
    //数据库表的建立
    QSqlQuery query;
    // 禁用外键约束
    query.exec("PRAGMA foreign_keys = false");

    // 删除表格
    query.exec("DROP TABLE IF EXISTS 'do-thing'");

    // 创建表格
    query.exec("CREATE TABLE 'do-thing' ("
               " 'id' INTEGER NOT NULL,"
               " 'Time' DATE,"
               " 'things' TEXT,"
               " 'finsh' integer DEFAULT 0,"
               " PRIMARY KEY ('id')"
               ")");

    // 创建唯一索引 以时间和事件为联合主键
    query.exec("CREATE UNIQUE INDEX 'unique_columns' ON 'do-thing' ('Time' ASC, 'things' ASC)");

    // 启用外键约束
    query.exec("PRAGMA foreign_keys = true");

    // 检查执行结果
    if (query.lastError().isValid()) {
        qDebug() << "Error creating table:" << query.lastError().text();
    } else {
        qDebug() << "Table created successfully.";
    }



    listmod=new  QSqlQueryModel();
    //选择未完成的事件，按时间升序排列
    listmod->setQuery("select * from 'do-thing' WHERE finsh==0 ORDER BY Time  ;") ;
    ui->listView->setModel(listmod);
    ui->listView->setModelColumn(2);
    ui->listView->update();
}

void memo::updata_codeforce()
{
    //调用请求函数
    request.run();
    //重新加载
    reload();
}

void memo::chang_indix(const QModelIndex &index)
{
    //更新字体
    auto tzzt=[](QLabel *label){
        // 设置自动换行
        label->setWordWrap(true);

        // 设置对齐方式，可以根据需要设置
        label->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    };
    //得到数据赋值给文本框
    QVariant data = listmod->data(index, Qt::DisplayRole);
    QString str=data.toString();
    ui->do_thing->setText(str);
    tzzt(ui->do_thing);
    data = listmod->data(index.siblingAtColumn(1), Qt::DisplayRole);
    str=data.toString();
    ui->do_time->setText(str);
    tzzt(ui->do_time);
}

void memo::reload()
{
    //重新加载
    listmod->setQuery("select * from 'do-thing' WHERE finsh==0 ORDER BY Time  ;");
    ui->listView->update();
}

void memo::determine()
{
    QSqlQuery q(data_base);
            //查找先到达的时间事件
            q.exec("SELECT * FROM 'do-thing' WHERE time >= '"+data_time::getInstance().data()+"' and finsh=0 ORDER BY time ASC LIMIT 1;");
            q.next();
            //判断时间是否相等
    if(data_time::getInstance().data()==q.value(1).toString())
    {

        data_base.exec("UPDATE 'do-thing'\
                       SET finsh=1\
                       WHERE uid = "+q.value(0).toString()+";");
        //弹出提示框
        m_snackbar->addMessage(q.value(2).toString());
        //重新加载
        reload();
    }

}
