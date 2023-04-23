/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H
#include "dirtree.h"
#include "mainwindow.h"

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <QtWidgets/QDialog>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsScene>
#include <QStringListModel>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *open;
    QMenu *menu;
    QAction *m1,*m2;
    QMenuBar *mb;
    QStatusBar *sb;
    openfileDialog *openfile;
    QListView *listView;
    QStringListModel *m;
    QSplitter *splitter;
    QGraphicsView *graph;
    QGraphicsScene *sence;
    TreeMenu *tm;

    void setupUi(MainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("SourceView"));
        MainWindow->resize(1000, 600);
        mb = new QMenuBar(MainWindow);
        mb->setGeometry(QRect(0, 0, 800, 26));
        open = new QAction("Open",mb);
        mb->addAction(open);
        menu = new QMenu(mb);
        menu->setTitle("menu");
        m1 = new QAction("m1",menu);
        m2 = new QAction("m2",menu);
        menu->addAction(m1);
        menu->addAction(m2);
        mb->addMenu(menu);
        sb = new QStatusBar(MainWindow);
        MainWindow->setMenuBar(mb);
        MainWindow->setStatusBar(sb);

        openfile = new openfileDialog;
        QObject::connect(openfile->okButton,SIGNAL(clicked(bool)),MainWindow,SLOT(on_open_file_yes(bool)));
        QObject::connect(openfile->cancalButton,SIGNAL(clicked(bool)),MainWindow,SLOT(on_open_file_no(bool)));


        splitter = new QSplitter(Qt::Horizontal,0);
        tm = new TreeMenu(splitter);
        //tm->CreateTopItem("ter-c");
        listView = new QListView(splitter);
        m = new QStringListModel();
        //m->setStringList(QStringList()<<"a"<<"b"<<"c"<<"d"<<"e"<<"f"<<"g"<<"h");
        listView->setModel(m);

        graph = new QGraphicsView(splitter);
        sence = new QGraphicsScene(graph);
        sence->setSceneRect(0,0,500,500);
        graph->setScene(sence);
        splitter->setStretchFactor(1,1);
        MainWindow->setCentralWidget(splitter);

        retranslateUi(MainWindow);

        QObject::connect(listView,SIGNAL(clicked(const QModelIndex &)),MainWindow,SLOT(on_listView_clicked(const QModelIndex &)));
        QObject::connect(open,SIGNAL(triggered()),MainWindow,SLOT(on_menu_checked()));
        //QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(MainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("SourceView", "SourceView", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
