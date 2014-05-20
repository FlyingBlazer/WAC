#include "cardetail.h"
#include "ui_cardetail.h"

CarDetail::CarDetail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CarDetail)
{
    ui->setupUi(this);
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
