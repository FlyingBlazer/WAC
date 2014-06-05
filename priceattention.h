#ifndef PRICEATTENTION_H
#define PRICEATTENTION_H

#include <QDialog>

namespace Ui {
class PriceAttention;
}

class PriceAttention : public QDialog
{
    Q_OBJECT

public:
    explicit PriceAttention(int x,QWidget *parent = 0);
    ~PriceAttention();

private:
    Ui::PriceAttention *ui;
};

#endif // PRICEATTENTION_H
