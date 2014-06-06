#include "selectcar.h"
#include "ui_selectcar.h"
#include "selectwidget.h"
#include "selectitem.h"
#include "settings.h"
#include "clientinfo.h"
#include <QDesktopWidget>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QListWidget>
#include <QListWidgetItem>
#include <QProcessEnvironment>
#include <QLabel>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QEventLoop>

SelectCar::SelectCar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectCar)
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
    connect(&NAM,&QNetworkAccessManager::finished,this,&SelectCar::finished);
}

SelectCar::~SelectCar()
{
    delete ui;
}

void SelectCar::finished(QNetworkReply *reply)
{
    QByteArray raw=reply->readAll();
    QJsonObject JObj=QJsonDocument::fromJson(raw).object();
    QJsonArray JArr=JObj["cars"].toArray();
    int count=0;
    QList<SelectItem *> items;
    foreach (QJsonValue i, JArr) {
        SelectItem *item=new SelectItem(
                    i.toObject().value("id").toInt(),
                    i.toObject().value("name_in_detail").toString(),
                    i.toObject().value("price").toDouble(),
                    i.toObject().value("days").toInt());
        items.append(item);
        connect(item,&SelectItem::selected,this,&SelectCar::select);
    }
    SelectWidget *w=new SelectWidget(items,panel);
    w->setFixedWidth(this->width()-30);
    panel->setWidget(w);
    emit finish(0);
}

void SelectCar::fetchCarList()
{
    ClientInfo *ci=ClientInfo::getInstance();
    QNetworkRequest request(QUrl(Settings::RecommandCar));
    QByteArray data;
    data.append("username=").append(ci->getName()).append("&token=").append(ci->getToken());
    data=QUrl(data).toEncoded();
    NAM.post(request,data);
}

int SelectCar::exec()
{
    fetchCarList();
    QEventLoop loop;
    connect(this,&SelectCar::finish,&loop,&QEventLoop::exit);
    loop.exec();
    return QDialog::exec();
}

void SelectCar::addRecommandCars()
{
    QNetworkRequest request(QUrl(Settings::RecommandCar));
    QByteArray postData;
    ClientInfo *ci=ClientInfo::getInstance();
    postData.append("username=").append(ci->getName())
            .append("&token=").append(ci->getToken());
    postData=QUrl(postData).toEncoded();
    NAM.post(request,postData);
    connect(&NAM,&QNetworkAccessManager::finished,this,&SelectCar::finished);
}

void SelectCar::select(int id) {
    emit selected(id);
    accept();
}
