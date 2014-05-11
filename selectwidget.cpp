#include "selectwidget.h"
#include "selectitem.h"
#include <QLayout>
#include <QVBoxLayout>

SelectWidget::SelectWidget(QWidget *parent) :
    QWidget(parent)
{
    setLayout(new QVBoxLayout());
}

void SelectWidget::addItem(QString id)
{
    SelectItem *item=new SelectItem(id,this);
    layout()->addWidget(item);
}
