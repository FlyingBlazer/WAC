#ifndef EXINCOME_H
#define EXINCOME_H

#include <QDialog>
#include <QNetworkAccessManager>

namespace Ui {
class ExIncome;
}

class ExIncome : public QDialog
{
    Q_OBJECT

public:
    explicit ExIncome(QWidget *parent = 0);
    ~ExIncome();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ExIncome *ui;
    QNetworkAccessManager NAM;
};

#endif // EXINCOME_H
