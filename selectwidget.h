#ifndef SELECTWIDGET_H
#define SELECTWIDGET_H

#include <QWidget>

class SelectWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SelectWidget(QWidget *parent = 0);

    void addItem(QString id);

signals:

public slots:

};

#endif // SELECTWIDGET_H
