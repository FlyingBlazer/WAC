#include "exincome.h"
#include "ui_exincome.h"
#include "clientinfo.h"
#include "settings.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrl>
#include <QDesktopWidget>
#include <QProcessEnvironment>

ExIncome::ExIncome(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExIncome)
{
    ui->setupUi(this);
    QRect applicationGeometry=QApplication::desktop()->availableGeometry();
    this->move((applicationGeometry.width()-this->width())/2,(applicationGeometry.height()-this->height())/2);
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
