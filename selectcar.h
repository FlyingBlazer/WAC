#ifndef SELECTCAR_H
#define SELECTCAR_H

#include <QDialog>
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

signals:
    void selected(long);

private:
    Ui::SelectCar *ui;
    TouchableScrollArea *panel;
};

#endif // SELECTCAR_H
