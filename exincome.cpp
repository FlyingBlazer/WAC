#include "exincome.h"
#include "ui_exincome.h"
#include "clientinfo.h"
#include "settings.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrl>

ExIncome::ExIncome(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExIncome)
{
    ui->setupUi(this);
}

ExIncome::~ExIncome()
{
    delete ui;
}

void ExIncome::on_pushButton_clicked()
{
    ClientInfo *ci=ClientInfo::getInstance();
    ci->income(ui->lineEdit->text().toInt());
    accept();
}
