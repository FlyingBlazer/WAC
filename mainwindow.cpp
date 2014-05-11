#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sampledialog.h"
#include "sign.h"
#include "login.h"
#include "settings.h"
#include "selectcar.h"
#include "clientinfo.h"
#include "showclientinfo.h"
#include <QDesktopWidget>
#include <QProcessEnvironment>
#include <QSettings>

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
    QSettings setting("buaa.GBK","WAC");
    setting.clear();
}

void MainWindow::on_pushButton_6_clicked()
{
    ShowClientInfo s;
    s.exec();
}
