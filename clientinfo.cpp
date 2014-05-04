#include "clientinfo.h"
#include "clientinfocollector.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkRequest>

ClientInfo ClientInfo::Instance;

ClientInfo &ClientInfo::getInstance()
{
    return Instance;
}

ClientInfo &ClientInfo::newClient(QString username, QString email, QString token)
{
    Instance.Name=username;
    Instance.Email=email;
    Instance.Token=token;
    Instance.inputClientInfo();
    Instance.saveToFile();
    return Instance;
}

ClientInfo::ClientInfo(QObject *parent) :
    QObject(parent)
{
    if(!QFile::exists(getExternalStorageDirectory()+"/WAC/user.dat"))
    {
        Data.setFileName(getExternalStorageDirectory()+"/WAC/user.dat");
        Data.open(QIODevice::ReadWrite);
        State=NotLogin;
        return;
    }
    Data.setFileName(getExternalStorageDirectory()+"/WAC/user.dat");
    Data.open(QIODevice::ReadWrite);
    readFromFile();
}

QByteArray ClientInfo::getAvatarBase64() const
{
    return AvatarBase64;
}

void ClientInfo::setAvatarBase64(const QByteArray &value)
{
    AvatarBase64 = value;
}


QString ClientInfo::getEmail() const
{
    return Email;
}

void ClientInfo::setEmail(const QString &value)
{
    Email = value;
}

ClientInfo::LoginState ClientInfo::getLoginState()
{
    return State;
}

void ClientInfo::setUid(long id)
{
    uid=id;
    refresh();
    saveToFile();
}

QString ClientInfo::getToken() const
{
    return Token;
}

void ClientInfo::setToken(const QString &value)
{
    Token = value;
}

QString ClientInfo::getNickname() const
{
    return Nickname;
}

void ClientInfo::setNickname(const QString &value)
{
    Nickname = value;
}

QString ClientInfo::getName() const
{
    return Name;
}

void ClientInfo::setName(const QString &value)
{
    Name = value;
}

void ClientInfo::refresh()
{
    QNetworkAccessManager NAM;
    QNetworkRequest request(QUrl(Settings::ClientInfoPage));
    request.setRawHeader("Content-Type","application/x-www-form-urlencoded");
//    request.setRawHeader("Accept","text/html,application/xhtml+xml,"
//                         "application/xml;q=0.9,image/webp,*/*;q=0.8");
//    request.setRawHeader("Accept-Encoding","gzip,deflate,sdch");
//    request.setRawHeader("User-Agent","Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36"
//                         " (KHTML, like Gecko) Chrome/33.0.1750.146 Safari/537.36");
    QByteArray postData;
    postData.append("uid=").append(QString::number(uid))
            .append("&magic=").append(Settings::Magic);
    NAM.post(request,postData);

    connect(&NAM,&QNetworkAccessManager::finished,this,&ClientInfo::setClientInfo);
}

void ClientInfo::setClientInfo(QNetworkReply *reply)
{
    QByteArray raw=reply->readAll();
    QJsonObject JObj=QJsonDocument::fromJson(raw).object();
    Name=JObj["Name"].toString();
    Nickname=JObj["Nickname"].toString();
    AvatarBase64=JObj["Avatar"].toString().toLocal8Bit();
    emit finished();
}

void ClientInfo::readFromFile()
{
    QByteArray data=QByteArray::fromBase64(Data.readAll());
    QJsonObject JObj=QJsonDocument::fromJson(data).object();
    Name=JObj["Name"].toString();
    Nickname=JObj["Nickname"].toString();
    AvatarBase64=JObj["Avatar"].toString().toLocal8Bit();
    State=HasLogin;
}

void ClientInfo::saveToFile()
{
    QJsonObject JObj;
    JObj.insert("Name",QJsonValue(Name));
    JObj.insert("NickName",QJsonValue(Nickname));
    JObj.insert("Avatar",QJsonValue(QString(AvatarBase64.toBase64())));
    QByteArray d=QJsonDocument(JObj).toJson();
    Data.write(d);
}

void ClientInfo::inputClientInfo()
{
    ClientInfoCollector cic;
    connect(&cic,&ClientInfoCollector::data,[this](QString nickname,QByteArray picdata){
        Nickname=nickname;
        AvatarBase64=picdata;
    });
    cic.exec();
}
