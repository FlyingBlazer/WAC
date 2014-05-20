#ifndef CLIENTINFOCOLLECTOR_H
#define CLIENTINFOCOLLECTOR_H

#include <QDialog>

namespace Ui {
class ClientInfoCollector;
}

class ClientInfoCollector : public QDialog
{
    Q_OBJECT

public:
    explicit ClientInfoCollector(QWidget *parent = 0);
    ~ClientInfoCollector();

signals:
    void data(QString, bool, int, QString, int);

private slots:
    void on_okButton_clicked();

private:
    Ui::ClientInfoCollector *ui;
    QByteArray PicData;
};

#endif // CLIENTINFOCOLLECTOR_H
