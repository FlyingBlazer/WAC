#include "sampledialog.h"
#include "ui_sampledialog.h"
#include "settings.h"
#include <QEventLoop>
#include <QDesktopWidget>
#include <QProcessEnvironment>

SampleDialog::SampleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SampleDialog)
{
    ui->setupUi(this);
    if(QProcessEnvironment::systemEnvironment().value("OS")!=QString("Windows_NT"))
    {
        QRect applicationGeometry=QApplication::desktop()->availableGeometry();
        this->setFixedSize(applicationGeometry.size());
    }
    ui->textBrowser->viewport()->setAttribute(Qt::WA_AcceptTouchEvents);
}

SampleDialog::~SampleDialog()
{
    delete ui;
}

void SampleDialog::on_pushButton_2_clicked()
{
    QNetworkRequest request1(QUrl("https://wac-wantacar.rhcloud.com/doc.html"));
    QNetworkReply *reply1=NAM.get(request1);
    QEventLoop loop1;
    QMetaObject::Connection a1=connect(&NAM,&QNetworkAccessManager::finished,[&loop1](){loop1.exit();});
    loop1.exec();
    ui->textBrowser->setText(QString(reply1->readAll()));
    NAM.disconnect(a1);
    return;

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
