#include "cardetail.h"
#include "ui_cardetail.h"
#include "settings.h"
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>

CarDetail::CarDetail(int id, QWidget *parent) :
    QDialog(parent),id(id),ui(new Ui::CarDetail)
{
    ui->setupUi(this);
    QNetworkRequest request(QUrl(Settings::CarDetailpage));
    QByteArray data;
    data.append("id=").append(QString::number(id));
    NAM.post(request,data);
    connect(&NAM,&QNetworkAccessManager::finished,this,&CarDetail::finished);
}

CarDetail::~CarDetail()
{
    delete ui;
}

long CarDetail::getId() const
{
    return id;
}

void CarDetail::setId(long value)
{
    id = value;
}

void CarDetail::finished(QNetworkReply *r)
{
    QByteArray raw=r->readAll();
    QJsonObject JObj=QJsonDocument::fromJson(raw).object();
    if(JObj["status"].toString()=="fail")
    {
        QMessageBox::warning(0,QString("错误"),JObj["msg"].toString());
        return;
    }
    QJsonObject info=JObj["info"].toObject();
    QStringList stl;
    foreach(QString key,info.keys())
    {
        stl.append(key+":"+info.value(key).toString());
    }
    ui->listWidget->addItems(stl);
}
