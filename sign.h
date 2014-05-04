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

signals:
    void succeed();

private slots:
    void on_acceptButton_clicked();

private:
    Ui::Sign *ui;
    QNetworkAccessManager NAM;
    QByteArray signUp(const QString &username, const QString &password, const QString &email);
};

#endif // SIGN_H
