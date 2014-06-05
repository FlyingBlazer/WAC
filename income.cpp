#include "income.h"
#include "ui_income.h"
#include "clientinfo.h"

Income::Income(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Income)
{
    ui->setupUi(this);
}

Income::~Income()
{
    delete ui;
}

void Income::on_acceptButton_clicked()
{
    ClientInfo *ci=ClientInfo::getInstance();
    ci->income(ui->incomeEdit->text().toInt());
    accept();
}
