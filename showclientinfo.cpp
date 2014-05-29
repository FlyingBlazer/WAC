#include "showclientinfo.h"
#include "ui_showclientinfo.h"
#include "clientinfo.h"

ShowClientInfo::ShowClientInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowCLientInfo)
{
    ui->setupUi(this);
    ClientInfo *a=ClientInfo::getInstance(this);
    ui->NickNameLable->setText(a->getNickname());
    ui->IncomeLable->setText(QString::number(a->getIncome()));
    ui->EducationLable->setText(a->getEducation());
}

ShowClientInfo::~ShowClientInfo()
{
    delete ui;
}
