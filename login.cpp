#include "login.h"
#include "ui_login.h"
#include "settings.h"

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QJsonDocument>
#include <QJsonObject>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    QRect applicationGeometry=QApplication::desktop()->availableGeometry();
    this->setFixedSize(applicationGeometry.size());
}

Login::~Login()
{
    delete ui;
}

QByteArray Login::login(QString username, QString password)
{
    QNetworkRequest request(QUrl(Settings::LoginPage));
    request.setRawHeader("Content-Type","application/x-www-form-urlencoded");
//    request.setRawHeader("Accept","text/html,application/xhtml+xml,"
//                         "application/xml;q=0.9,image/webp,*/*;q=0.8");
//    request.setRawHeader("Accept-Encoding","gzip,deflate,sdch");
//    request.setRawHeader("User-Agent","Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36"
//                         " (KHTML, like Gecko) Chrome/33.0.1750.146 Safari/537.36");
    QByteArray postData;
    postData.append("username=").append(username).append("&password=")
            .append(QCryptographicHash::hash(password.toLatin1(),QCryptographicHash::Md5))
            .append("&magic=").append(Settings::Magic);

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
        QMessageBox::information(this,"登陆成功",JObj["token"].toString());
    }
}
