#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "clientinfo.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_selectButton_clicked();

    void on_incomeButton_clicked();

    void on_exIncomeButton_clicked();

    void showPriceAttention(int x);

    void infogot();

private:
    Ui::MainWindow *ui;
    void checkPrice();
    ClientInfo *ci;
};

#endif // MAINWINDOW_H
