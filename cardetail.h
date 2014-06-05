#ifndef CARDETAIL_H
#define CARDETAIL_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <touchablescrollarea.h>

namespace Ui {
class CarDetail;
}

class CarDetail : public QDialog
{
    Q_OBJECT

public:
    explicit CarDetail(int id,QWidget *parent = 0);
    ~CarDetail();

    long getId() const;
    void setId(long value);

private:
    Ui::CarDetail *ui;
    long id;
    QNetworkAccessManager NAM;
    void finished(QNetworkReply *);
    TouchableScrollArea *panel;
};

#endif // CARDETAIL_H
