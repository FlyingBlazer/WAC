#include "selectwidget.h"
#include "selectitem.h"
#include <QLayout>
#include <QtDebug>

SelectWidget::SelectWidget(QList<SelectItem *> items, QWidget *parent) :
    QWidget(parent)
{
    lay=new QVBoxLayout(this);
    setLayout(lay);
    foreach(SelectItem *item, items) {
        item->setParent(this);
        lay->addWidget(item);
    }
}
