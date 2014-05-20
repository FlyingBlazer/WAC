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
    SelectItem(QString id, QWidget *parent = 0);
    ~SelectItem();

signals:
    void selected();

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

private:
    Ui::SelectItem *ui;
    QString id;
    QNetworkAccessManager NAM;
    QPixmap pix;
    QTime PressTime;
    CarDetail *detail;
    void load();

private slots:
    void onLoaded(QNetworkReply *);
    void onImageLoaded(QNetworkReply *);
};

#endif // SELECTITEM_H
