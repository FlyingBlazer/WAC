#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sampledialog.h"
#include "sign.h"
#include "login.h"
#include "settings.h"
#include <QDesktopWidget>
#include <QProcessEnvironment>
#include "selectcar.h"
#include "clientinfo.h"
#include "showclientinfo.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if(QProcessEnvironment::systemEnvironment().value("OS")!=QString("Windows_NT"))
    {
        QRect applicationGeometry=QApplication::desktop()->availableGeometry();
        this->setFixedSize(applicationGeometry.size());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    SampleDialog dialog;
    dialog.exec();
}

void MainWindow::on_pushButton_2_clicked()
{
    Sign a;
    connect(&a,&Sign::succeed,this,&MainWindow::on_pushButton_3_clicked);
    a.exec();
}

void MainWindow::on_pushButton_3_clicked()
{
    Login a;
    a.exec();
}

void MainWindow::on_pushButton_4_clicked()
{
    SelectCar a;
    a.exec();
}

void MainWindow::on_pushButton_5_clicked()
{
    ClientInfo::newClient("test","test","test",this);
}

void MainWindow::on_pushButton_6_clicked()
{
    ShowClientInfo s;
    s.exec();
}
