#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScreen>
#include <QAction>
#include <QDebug>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class openfileDialog : public QDialog
{
public:
    QLineEdit *fileNameEdit;
    QPushButton *okButton;
    QPushButton *cancalButton;

    openfileDialog()
    {
        QLabel *fileNameLabel = new QLabel("path");
        fileNameEdit = new QLineEdit();
        okButton = new QPushButton("确定");
        cancalButton = new QPushButton("取消");
        QHBoxLayout *Hlayout1 = new QHBoxLayout();
        Hlayout1->addWidget(fileNameLabel);
        Hlayout1->addWidget(fileNameEdit);
        QHBoxLayout *Hlayout2 = new QHBoxLayout();
        Hlayout2->addWidget(okButton);
        Hlayout2->addWidget(cancalButton);
        QVBoxLayout *MainVlayout = new QVBoxLayout(this);
        MainVlayout->addLayout(Hlayout1);
        MainVlayout->addLayout(Hlayout2);
        this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_listView_clicked(const QModelIndex &index);
    void on_menu_checked();
    void on_open_file_yes(bool);
    void on_open_file_no(bool);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
