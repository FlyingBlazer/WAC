#include "daylyrecord.h"
#include "ui_daylyrecord.h"
#include <QMessageBox>
#include "clientinfo.h"

DaylyRecord::DaylyRecord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DaylyRecord)
{
    ui->setupUi(this);
}

DaylyRecord::~DaylyRecord()
{
    delete ui;
}

void DaylyRecord::on_acceptButton_clicked()
{
    if(ui->inputEdit->text().length()==0)
    {
        QMessageBox::warning(this,"","请输入本日结余");
        return;
    }
    ClientInfo *ci=ClientInfo::getInstance();
    ci->setExpense(ui->inputEdit->text().toInt());
    ci->commit();
}
