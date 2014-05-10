#include "clientinfocollector.h"
#include "ui_clientinfocollector.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QProcessEnvironment>
#include <QDesktopWidget>

ClientInfoCollector::ClientInfoCollector(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClientInfoCollector)
{
    ui->setupUi(this);
    if(QProcessEnvironment::systemEnvironment().value("OS")!=QString("Windows_NT"))
    {
        QRect applicationGeometry=QApplication::desktop()->availableGeometry();
        this->setFixedSize(applicationGeometry.size());
    }
}

ClientInfoCollector::~ClientInfoCollector()
{
    delete ui;
}

void ClientInfoCollector::on_okButton_clicked()
{
    if(ui->nicknameInput->text().length()==0)
    {
        QMessageBox::warning(this,tr("错误"),tr("请填写昵称"));
        return;
    }
    if(ui->incomeInput->text().length()==0)
    {
        QMessageBox::warning(this,tr("错误"),tr("请填写月收入"));
        return;
    }
    if(ui->educationInput->text().length()==0)
    {
        QMessageBox::warning(this,tr("错误"),tr("请填写学历"));
        return;
    }
    emit data(ui->nicknameInput->text(),ui->sexInput->currentText(),
              ui->incomeInput->text(),ui->educationInput->text());
    accept();
}
