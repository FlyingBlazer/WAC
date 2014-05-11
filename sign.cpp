#include "sign.h"
#include "ui_sign.h"
#include "settings.h"
#include "clientinfo.h"
#include <QMessageBox>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDesktopWidget>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QProcessEnvironment>

Sign::Sign(QWidget *parent) :
    QDialog(parent),ui(new Ui::Sign)
{
    ui->setupUi(this);
    if(QProcessEnvironment::systemEnvironment().value("OS")!=QString("Windows_NT"))
    {
        QRect applicationGeometry=QApplication::desktop()->availableGeometry();
        this->setFixedSize(applicationGeometry.size());
    }
}

Sign::~Sign()
{
    delete ui;
}

QByteArray Sign::signUp(const QString &username,const QString &password,const QString &email)
{
    QNetworkRequest request(QUrl(Settings::SignPage));
    request.setRawHeader("Content-Type","application/x-www-form-urlencoded");
//    request.setRawHeader("Accept","text/html,application/xhtml+xml,"
//                         "application/xml;q=0.9,image/webp,*/*;q=0.8");
//    request.setRawHeader("Accept-Encoding","gzip,deflate,sdch");
//    request.setRawHeader("User-Agent","Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36"
//                         " (KHTML, like Gecko) Chrome/33.0.1750.146 Safari/537.36");
    QByteArray postData;
    postData.append("username=").append(username).append("&password=")
            .append(QCryptographicHash::hash(password.toLatin1(),QCryptographicHash::Md5))
            .append("&email=").append(email).append("&magic=").append(Settings::Magic);

    NAM.post(request,postData);

    QNetworkReply *reply=NAM.post(request,postData);

    void (QNetworkReply:: *E)(QNetworkReply::NetworkError)=&QNetworkReply::error;

    QMetaObject::Connection b=connect(reply,E,[&reply](QNetworkReply::NetworkError err){
        qDebug() << static_cast<int>(err);
        qDebug() << reply->errorString();
        QMessageBox ErrMsg;
        ErrMsg.setText(reply->errorString());
        ErrMsg.exec();
    });

    QEventLoop loop;
    QMetaObject::Connection a=connect(&NAM,&QNetworkAccessManager::finished,[&loop](){loop.exit();});
    loop.exec();
    NAM.disconnect(a);
    reply->disconnect(b);

    QByteArray response=reply->readAll();
    reply->deleteLater();
    return response;
}

void Sign::on_acceptButton_clicked()
{
    QString username=ui->usernameEdit->text(),
            password=ui->passwordEdit->text(),
            confirmpass=ui->confirmPasswordEdit->text(),
            email=ui->emailEdit->text();
    if(password!=confirmpass)
    {
        QMessageBox::warning(this,"Error","密码输入错误");
        return;
    }
    QByteArray response=signUp(username,password,email);
    QJsonObject JObj=QJsonDocument::fromJson(response).object();
    if(JObj["status"].toString()!="ok")
    {
        QMessageBox::warning(this,"注册失败",JObj["msg"].toString());
        return;
    }
    QMessageBox::information(this,"注册成功",JObj["msg"].toString());

    ClientInfo *client=ClientInfo::newClient(username,email,JObj["token"].toString(),true);

    emit succeed();
    accept();
}
