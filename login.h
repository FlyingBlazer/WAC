#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QNetworkAccessManager>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:
    void on_loginButton_clicked();

private:
    Ui::Login *ui;
    QNetworkAccessManager NAM;
};

#endif // LOGIN_H
