#include "priceattention.h"
#include "ui_priceattention.h"
#include "clientinfo.h"
#include "selectcar.h"
#include <QDesktopWidget>

PriceAttention::PriceAttention(int x, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PriceAttention)
{
    ui->setupUi(this);
    QRect applicationGeometry=QApplication::desktop()->availableGeometry();
    this->move((applicationGeometry.width()-this->width())/2,(applicationGeometry.height()-this->height())/2);
    ui->label->setText(ui->label->text()+QString::number(x)+"元！");
}

PriceAttention::~PriceAttention()
{
    delete ui;
}

void PriceAttention::on_pushButton_clicked()
{
    ClientInfo *ci=ClientInfo::getInstance();
    SelectCar sc;
    connect(&sc,&SelectCar::selected,ci,&ClientInfo::selectCar);
    qDebug("connected");
    sc.exec();
    disconnect(&sc,&SelectCar::selected,ci,&ClientInfo::selectCar);
    accept();
}
