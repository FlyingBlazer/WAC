#include "selectitem.h"
#include "ui_selectitem.h"
#include "settings.h"
#include <QPushButton>
#include <QJsonDocument>
#include <QJsonObject>
#include <QPixmap>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QMenu>
#include <QAction>
#include <QMouseEvent>

SelectItem::SelectItem(int id, QString name, double price, int day, QWidget *parent) :
    QWidget(parent),ui(new Ui::SelectItem),id(id)
{
    ui->setupUi(this);
    ui->NameLable->setText(name);
    ui->price->setText("售价："+QString::number(price)+"万人民币");
    ui->time->setText("您还需"+QString::number(day)+"天可以购买");
    connect(ui->SelectButton,&QPushButton::clicked,this,&SelectItem::select);
}

SelectItem::~SelectItem()
{
    delete ui;
}

void SelectItem::mousePressEvent(QMouseEvent *e)
{
//    if(e->buttons().testFlag(Qt::LeftButton))
//    {
//        PressTime=QTime::currentTime();
//    }
}

void SelectItem::mouseReleaseEvent(QMouseEvent *e)
{
//    if(e->buttons().testFlag(Qt::LeftButton))
//    {
//        if(PressTime.secsTo(QTime::currentTime())<1)
//        {
//            detail->setId(id.toLong());
//            connect(detail,&CarDetail::accepted,static_cast<QWidget *>(this->parent()),&QWidget::close);
//            detail->exec();
//        }
//    }
}

void SelectItem::select()
{
    emit selected(id);
}

void SelectItem::on_DetailButton_clicked()
{
    CarDetail d(id,this);
    d.exec();
}
