#include "login.h"
#include "ui_login.h"
#include "settings.h"
#include "clientinfo.h"
#include "sign.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QJsonDocument>
#include <QJsonObject>
#include <QProcessEnvironment>
#include <QUrl>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    if(QProcessEnvironment::systemEnvironment().value("OS")!=QString("Windows_NT"))
    {
        QRect applicationGeometry=QApplication::desktop()->availableGeometry();
        this->setFixedSize(applicationGeometry.size());
    }
}

Login::~Login()
{
    delete ui;
}

QByteArray Login::login(QString username, QString password)
{
    QNetworkRequest request(QUrl(Settings::LoginPage));
    request.setRawHeader("Content-Type","application/x-www-form-urlencoded");
    QByteArray postData;
    postData.append("username=").append(username).append("&password=")
            .append(QCryptographicHash::hash(password.toLatin1(),QCryptographicHash::Md5));
    postData=QUrl(postData).toEncoded();

    QNetworkReply *reply=NAM.post(request,postData);

    void (QNetworkReply:: *E)(QNetworkReply::NetworkError)=&QNetworkReply::error;

    QMetaObject::Connection b=connect(reply,E,[&reply](QNetworkReply::NetworkError err){
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

void Login::on_loginButton_clicked()
{
    QString username=ui->UserNameEdit->text();
    QString password=ui->PasswordEdit->text();
    QByteArray response=login(username,password);
    QJsonObject JObj=QJsonDocument::fromJson(response).object();
    if(JObj["status"].toString()!="ok")
    {
        QMessageBox::warning(this,"登录失败",JObj["msg"].toString());
        return;
    } else {
        ClientInfo::newClient(username,QString(),JObj["token"].toString());
    }
    accept();
}

void Login::on_pushButton_clicked()
{
    this->close();
    this->deleteLater();
    Sign s;
    s.exec();
}
