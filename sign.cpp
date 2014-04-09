#include "sign.h"
#include "ui_sign.h"
#include "settings.h"
#include <QMessageBox>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDesktopWidget>
#include <QtDebug>
#include <QMovie>
#include <QFile>
#include <QImageReader>

Sign::Sign(QWidget *parent) :
    QDialog(parent),ui(new Ui::Sign)
{
    ui->setupUi(this);
    QRect applicationGeometry=QApplication::desktop()->availableGeometry();
    this->setFixedSize(applicationGeometry.size());
    readCheckCode();
}

Sign::~Sign()
{
    delete ui;
}

void Sign::readCheckCode()
{
    CheckCode.load(":/um.png");
    qDebug() << CheckCode.size();
    ui->checkcode->setPixmap(CheckCode);
    qDebug() << CheckCode.size();
    this->Code="0000";
}

bool Sign::signUp(QString username,QString password)
{
    static int i=0;
    if(i++%2==0)
        return true;
    else
        return false;
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

    QString response(reply->readAll());
    reply->deleteLater();
    if(response=="ok")
        return true;
    else
        return false;
}

void Sign::on_acceptButton_clicked()
{
    QString username=ui->usernameEdit->text(),
            password=ui->passwordEdit->text(),
            confirmpass=ui->confirmPasswordEdit->text(),
            checkcode=ui->checkcodeEdit->text();
    if(checkcode!=this->Code)
    {
        QMessageBox::warning(this,"Error","验证码错误");
        return;
    }
    if(password!=confirmpass)
    {
        QMessageBox::warning(this,"Error","密码输入错误");
        return;
    }
    if(!signUp(username,password))
    {
        QMessageBox::warning(this,"Error","注册失败");
        return;
    }
    QMessageBox::information(this,"Succeed","注册成功");
    accept();
}
