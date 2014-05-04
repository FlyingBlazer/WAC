#include "clientinfocollector.h"
#include "ui_clientinfocollector.h"
#include <QFileDialog>
#include <QMessageBox>

ClientInfoCollector::ClientInfoCollector(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClientInfoCollector)
{
    ui->setupUi(this);
}

ClientInfoCollector::~ClientInfoCollector()
{
    delete ui;
}

void ClientInfoCollector::on_selectButton_clicked()
{
    QString path=QFileDialog::getOpenFileName(this,tr("选择头像"),"/",tr("图片文件 (*.png *.xpm *.jpg)"));
    QFile pic(path);
    pic.open(QIODevice::ReadOnly);
    PicData=pic.readAll().toBase64();
    pic.close();
}

void ClientInfoCollector::on_okButton_clicked()
{
    if(ui->nicknameInput->text().length()==0)
    {
        QMessageBox::warning(this,tr("错误"),tr("请填写昵称"));
        return;
    }
    if(PicData.isEmpty())
    {
        QMessageBox::warning(this,tr("错误"),tr("请选择头像"));
        return;
    }
    emit data(ui->nicknameInput->text(),PicData);
    accept();
}
