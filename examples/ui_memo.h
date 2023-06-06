/********************************************************************************
** Form generated from reading UI file 'memo.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MEMO_H
#define UI_MEMO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_memo
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QWidget *widget_2;
    QLabel *label;
    QListView *listView;
    QWidget *widget_appbar;

    void setupUi(QMainWindow *memo)
    {
        if (memo->objectName().isEmpty())
            memo->setObjectName(QString::fromUtf8("memo"));
        memo->resize(800, 600);
        memo->setMinimumSize(QSize(800, 600));
        memo->setMaximumSize(QSize(800, 600));
        memo->setDockOptions(QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks);
        centralwidget = new QWidget(memo);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 50, 800, 550));
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(174, 226, 255);"));
        widget->setInputMethodHints(Qt::ImhNone);
        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setGeometry(QRect(500, 0, 300, 550));
        widget_2->setStyleSheet(QString::fromUtf8("background-color: rgb(151, 222, 255);"));
        label = new QLabel(widget_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 10, 261, 221));
        label->setStyleSheet(QString::fromUtf8("color:white;font:60px \\\"Microsoft YaHei\\\",simhei;font-weight:regular;"));
        listView = new QListView(widget);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setGeometry(QRect(70, 40, 401, 481));
        widget_appbar = new QWidget(centralwidget);
        widget_appbar->setObjectName(QString::fromUtf8("widget_appbar"));
        widget_appbar->setGeometry(QRect(0, 0, 800, 50));
        widget_appbar->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 210, 255);"));
        memo->setCentralWidget(centralwidget);

        retranslateUi(memo);

        QMetaObject::connectSlotsByName(memo);
    } // setupUi

    void retranslateUi(QMainWindow *memo)
    {
        memo->setWindowTitle(QCoreApplication::translate("memo", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("memo", "12:20:12\n"
"\346\230\237\346\234\237\344\272\214\n"
"6/12", nullptr));
    } // retranslateUi

};

namespace Ui {
    class memo: public Ui_memo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEMO_H
