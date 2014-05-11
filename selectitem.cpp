#include "selectitem.h"
#include "ui_selectitem.h"
#include "settings.h"
#include <QPushButton>
#include <QJsonDocument>
#include <QJsonObject>
#include <QPixmap>
#include <QNetworkAccessManager>
#include <QNetworkRequest>

SelectItem::SelectItem(QString id, QWidget *parent) :
    QWidget(parent),ui(new Ui::SelectItem),id(id)
{
    ui->setupUi(this);
}

SelectItem::~SelectItem()
{
    delete ui;
}

void SelectItem::load()
{
    QNetworkRequest request(QUrl(Settings::CarDetailpage+"?id="+id));
    NAM.get(request);
    connect(&NAM,&QNetworkAccessManager::finished,this,&SelectItem::onLoaded);
}

void SelectItem::onLoaded(QNetworkReply *r)
{
    disconnect(&NAM,0,0,0);
    QString ImageUrl;
    QByteArray reply=r->readAll();
    r->deleteLater();
    QJsonObject JObj=QJsonDocument::fromJson(reply).object();
    ImageUrl=JObj["Image"].toString();
    ui->NameLable->setText(JObj["Name"].toString());
    ui->DescriptionLabel->setText(JObj["Description"].toString());
    ui->DetailLable1->setText(JObj["Detail1"].toString());
    ui->DetailLable2->setText(JObj["Detail2"].toString());
    ui->DetailLable3->setText(JObj["Detail3"].toString());
    QNetworkRequest request(ImageUrl);
    NAM.get(request);
    connect(&NAM,&QNetworkAccessManager::finished,this,&SelectItem::onImageLoaded);
}

void SelectItem::onImageLoaded(QNetworkReply *r)
{
    disconnect(&NAM,0,0,0);
    pix.loadFromData(r->readAll());
    r->deleteLater();
    ui->ImageLable->setPixmap(pix);
}
