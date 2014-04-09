#ifndef SIGN_H
#define SIGN_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QMovie>
#include <QPixmap>

namespace Ui {
class Sign;
}

class Sign : public QDialog
{
    Q_OBJECT

public:
    explicit Sign(QWidget *parent = 0);
    ~Sign();

private slots:
    void on_acceptButton_clicked();

private:
    Ui::Sign *ui;
    QString Code;
    QPixmap CheckCode;
    QNetworkAccessManager NAM;
    bool signUp(QString username,QString password);
    void readCheckCode();
};

#endif // SIGN_H
