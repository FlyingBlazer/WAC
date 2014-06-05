#ifndef SELECTWIDGET_H
#define SELECTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include "selectitem.h"

class SelectWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SelectWidget(QList<SelectItem *> items,QWidget *parent = 0);

signals:

public slots:

private:
    QVBoxLayout *lay;

};

#endif // SELECTWIDGET_H
