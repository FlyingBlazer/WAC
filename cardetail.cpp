#include "cardetail.h"
#include "ui_cardetail.h"
#include "settings.h"
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QProcessEnvironment>
#include <QVBoxLayout>
#include <QLabel>

CarDetail::CarDetail(int id, QWidget *parent) :
    QDialog(parent),id(id),ui(new Ui::CarDetail)
{
    ui->setupUi(this);
    if(QProcessEnvironment::systemEnvironment().value("OS")!=QString("Windows_NT"))
    {
        QRect applicationGeometry=QApplication::desktop()->availableGeometry();
        this->setFixedSize(applicationGeometry.size());
    }
    panel=new TouchableScrollArea(this);
    ui->verticalLayout->insertWidget(0,panel);
    QWidget *w=new QWidget(panel);
    w->setFixedWidth(panel->width());
    panel->setWidget(w);
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
    QWidget *w = new QWidget(this);
    w->setFixedWidth(panel->width()-30);
    QVBoxLayout *lay=new QVBoxLayout();
    w->setLayout(lay);
    QByteArray raw=r->readAll();
    QJsonObject JObj=QJsonDocument::fromJson(raw).object();
    if(JObj["status"].toString()=="fail")
    {
        QMessageBox::warning(0,QString("错误"),JObj["msg"].toString());
        return;
    }
    QJsonObject info=JObj["info"].toObject();
    QLabel *l;
    foreach(QString key,info.keys())
    {
        l=new QLabel(key+":"+info.value(key).toString());
        lay->addWidget(l);
    }
    panel->setWidget(w);
}
