#include "mainwindow.h"
#include "main_ui.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    ui->sence->clear();
    ui->sence->addText(index.data().toString());
    //qDebug()<<index.data().toString();
}

void MainWindow::on_menu_checked()
{
    ui->openfile->setModal(true);
    auto r = this->geometry();
    auto d = ui->openfile->geometry();
    ui->openfile->move(r.x()+r.width()/2-d.width()/2,r.y()+r.height()/2-d.height()/2);
    ui->openfile->show();
}

void MainWindow::on_open_file_yes(bool)
{
    QDir *temp = new QDir;
    auto path = ui->openfile->fileNameEdit->text();
    bool exist = temp->exists(path);
    if(exist){
        ui->tm->model()->removeRows(0,ui->tm->model()->rowCount());
        ui->tm->CreateTopItem(path);
    } else {
        QMessageBox::warning(this,"open dir",path+" is not a dir");
    }
    ui->openfile->close();
}

void MainWindow::on_open_file_no(bool)
{
    ui->openfile->close();
}
