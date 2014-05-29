#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "selectcar.h"
#include "settings.h"
#include "income.h"
#include "exincome.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_selectButton_clicked()
{
    QEventLoop loop;
    SelectCar sc;
    QNetworkAccessManager NAM;
    QNetworkRequest request(QUrl(Settings::CarlistPage));
    NAM.get(request);
    connect(&NAM,&QNetworkAccessManager::finished,[&loop,&sc,this](QNetworkReply *reply){
        loop.exit();
        QJsonObject JObj=QJsonDocument::fromBinaryData(reply->readAll()).object();
        QJsonArray JArr=JObj["carlist"].toArray();
        QList<QString> carlist;
        for(int i=0;i<JArr.size();i++)
        {
            carlist.append(JArr[i].toString());
        }
        sc.setCarList(carlist);
    });
    loop.exec();
    sc.exec();
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
