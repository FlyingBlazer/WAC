#ifndef SELECTITEM_H
#define SELECTITEM_H

#include <QWidget>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QPixmap>
#include <QTime>
#include "cardetail.h"

namespace Ui {
class SelectItem;
}

class SelectItem : public QWidget
{
    Q_OBJECT

public:
    SelectItem(int id, QString name, double price, int day, QWidget *parent = 0);
    ~SelectItem();

signals:
    void selected(int);

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

private slots:
    void on_DetailButton_clicked();

private:
    Ui::SelectItem *ui;
    int id;
    QNetworkAccessManager NAM;
    QPixmap pix;
    QTime PressTime;
    void select();

};

#endif // SELECTITEM_H
