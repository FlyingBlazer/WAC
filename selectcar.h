#ifndef SELECTCAR_H
#define SELECTCAR_H

#include <QDialog>
#include <QList>
#include "touchablescrollarea.h"

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
};

#endif // SELECTCAR_H
