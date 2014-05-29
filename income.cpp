#include "income.h"
#include "ui_income.h"

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
