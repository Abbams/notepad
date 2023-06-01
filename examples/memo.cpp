#include "memo.h"
#include "ui_memo.h"
#include <QtWidgets/QVBoxLayout>
#include <QColorDialog>
#include <qtmaterialappbar.h>
#include <qtmaterialiconbutton.h>
#include <lib/qtmaterialtheme.h>
#include <QLabel>
memo::memo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::memo),
    appBar(new QtMaterialAppBar)
{
    ui->setupUi(this);
    QLabel *label = new QLabel("menu");
    label->setAttribute(Qt::WA_TranslucentBackground);
    label->setForegroundRole(QPalette::Foreground);
    label->setContentsMargins(6, 0, 0, 0);

    QPalette palette = label->palette();
    palette.setColor(label->foregroundRole(), Qt::white);
    label->setPalette(palette);

    label->setFont(QFont("Roboto", 18, QFont::Normal));

    QtMaterialIconButton *button = new QtMaterialIconButton(QtMaterialTheme::icon("navigation", "menu"));
    button->setIconSize(QSize(24, 24));
    appBar->appBarLayout()->addWidget(button);
    appBar->appBarLayout()->addWidget(label);
    appBar->appBarLayout()->addStretch(1);
    button->setColor(Qt::white);
    button->setFixedWidth(42);

    QVBoxLayout *layout = new QVBoxLayout;
    setLayout(layout);

    QWidget *widget = new QWidget;
    layout->addWidget(widget);

    QWidget *canvas = new QWidget;
    canvas->setStyleSheet("QWidget { background: white; }");
    layout->addWidget(canvas);

    layout->setContentsMargins(20, 20, 20, 20);

    layout = new QVBoxLayout;
    canvas->setLayout(layout);
    canvas->setMaximumHeight(300);
    layout->addWidget(appBar);
    layout->addStretch(1);
    appBar->setParent(this);
    appBar->setFixedSize({800,50});
    appBar->show();
}

memo::~memo()
{
    delete ui;
}
