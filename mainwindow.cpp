#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "selectcar.h"
#include "settings.h"
#include "income.h"
#include "exincome.h"
#include "priceattention.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QPushButton>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ci=ClientInfo::getInstance();
    connect(ci,&ClientInfo::infogot,this,&MainWindow::infogot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::checkPrice()
{
    QNetworkAccessManager NAM;
    QNetworkRequest request;
}

void MainWindow::infogot()
{
    qDebug("Info got!");
    int price=(int)(ci->getSelectedCarPrice()*10000);
    int dayincome=ci->getIncome()/30;
    int had=ci->getBalance();
    ui->lcdNumber->display((price-had)/dayincome);
    ui->lcdNumber_2->display(had/price);
    qDebug() << (price-had)/dayincome << endl << had/price;
}

void MainWindow::on_selectButton_clicked()
{
    SelectCar sc;
    connect(&sc,&SelectCar::selected,ci,&ClientInfo::selectCar);
    qDebug("connected");
    sc.exec();
    disconnect(&sc,&SelectCar::selected,ci,&ClientInfo::selectCar);
}

void MainWindow::on_incomeButton_clicked()
{
    Income in;
    in.exec();
}

void MainWindow::on_exIncomeButton_clicked()
{
    ExIncome ei;
    ei.exec();
}

void MainWindow::showPriceAttention(int x)
{
    PriceAttention att(x);
    connect(&att,&QDialog::accept,this,&MainWindow::on_selectButton_clicked);
    att.exec();
}
