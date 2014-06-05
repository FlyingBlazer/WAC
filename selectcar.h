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

    int exec();

public slots:
    void select(int);

signals:
    void selected(int);
    void finish(int);

private:
    Ui::SelectCar *ui;
    TouchableScrollArea *panel;
    QList<QString> CarList;
    QNetworkAccessManager NAM;
    void addRecommandCars();
    void fetchCarList();

private slots:
    void finished(QNetworkReply *);
};

#endif // SELECTCAR_H
