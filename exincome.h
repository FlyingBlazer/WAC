#ifndef EXINCOME_H
#define EXINCOME_H

#include <QDialog>

namespace Ui {
class ExIncome;
}

class ExIncome : public QDialog
{
    Q_OBJECT

public:
    explicit ExIncome(QWidget *parent = 0);
    ~ExIncome();

private:
    Ui::ExIncome *ui;
};

#endif // EXINCOME_H
