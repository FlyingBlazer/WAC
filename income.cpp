#include "income.h"
#include "ui_income.h"
#include "clientinfo.h"
#include <QDesktopWidget>
#include <QProcessEnvironment>

Income::Income(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Income)
{
    ui->setupUi(this);
    QRect applicationGeometry=QApplication::desktop()->availableGeometry();
    this->move((applicationGeometry.width()-this->width())/2,(applicationGeometry.height()-this->height())/2);
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
