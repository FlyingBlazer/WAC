#ifndef SELECTITEM_H
#define SELECTITEM_H

#include <QWidget>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QPixmap>

namespace Ui {
class SelectItem;
}

class SelectItem : public QWidget
{
    Q_OBJECT

public:
    SelectItem(QString id, QWidget *parent = 0);
    ~SelectItem();

private:
    Ui::SelectItem *ui;
    QString id;
    QNetworkAccessManager NAM;
    QPixmap pix;
    void load();

private slots:
    void onLoaded(QNetworkReply *);
    void onImageLoaded(QNetworkReply *);
};

#endif // SELECTITEM_H
