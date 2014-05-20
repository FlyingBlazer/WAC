#ifndef SELECTCAR_H
#define SELECTCAR_H

#include <QDialog>
#include <QList>
#include <QNetworkAccessManager>
#include "touchablescrollarea.h"

class QNetworkReply;

namespace Ui {
class SelectCar;
}

class SelectCar : public QDialog
{
    Q_OBJECT

public:
    explicit SelectCar(QWidget *parent = 0);
    ~SelectCar();

    QList<QString> getCarList() const;
    void setCarList(const QList<QString> &value);

    int exec();

signals:
    void selected(long);

private:
    Ui::SelectCar *ui;
    TouchableScrollArea *panel;
    QList<QString> CarList;
    QNetworkAccessManager NAM;
    void addRecommandCars();

private slots:
    void finished(QNetworkReply *);
};

#endif // SELECTCAR_H
