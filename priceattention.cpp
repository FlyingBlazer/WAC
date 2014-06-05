#include "priceattention.h"
#include "ui_priceattention.h"

PriceAttention::PriceAttention(int x, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PriceAttention)
{
    ui->setupUi(this);
    ui->label->setText(ui->label->text()+QString::number(x)+"元！");
}

PriceAttention::~PriceAttention()
{
    delete ui;
}
