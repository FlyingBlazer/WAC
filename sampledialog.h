#ifndef SAMPLEDIALOG_H
#define SAMPLEDIALOG_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

namespace Ui {
class SampleDialog;
}

class SampleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SampleDialog(QWidget *parent = 0);
    ~SampleDialog();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::SampleDialog *ui;
    QNetworkAccessManager NAM;
};

#endif // SAMPLEDIALOG_H
