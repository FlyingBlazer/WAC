#include "exincome.h"
#include "ui_exincome.h"

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
