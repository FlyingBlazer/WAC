#include "sampledialog.h"
#include "ui_sampledialog.h"
#include "settings.h"
#include <QEventLoop>
#include <QDesktopWidget>

SampleDialog::SampleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SampleDialog)
{
    ui->setupUi(this);
    QRect applicationGeometry=QApplication::desktop()->availableGeometry();
    this->setFixedHeight(applicationGeometry.height());
    this->setFixedWidth(applicationGeometry.width());
}

SampleDialog::~SampleDialog()
{
    delete ui;
}

void SampleDialog::on_pushButton_2_clicked()
{
    QByteArray postData;
    postData.append("magic=").append(ui->lineEdit->text());
    QNetworkRequest request(QUrl("https://wac-wantacar.rhcloud.com/api"));
    request.setRawHeader("Content-Type","application/x-www-form-urlencoded");
    QNetworkReply *reply=NAM.post(request,postData);
    QEventLoop loop;
    QMetaObject::Connection a=connect(&NAM,&QNetworkAccessManager::finished,[&loop](){loop.exit();});
    loop.exec();
    ui->textBrowser->setText(QString(reply->readAll()));
    NAM.disconnect(a);
}
