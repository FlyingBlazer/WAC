#include "clientinfo.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkRequest>

ClientInfo::ClientInfo(QObject *parent) :
    QObject(parent)
{
}

ClientInfo::LoginState ClientInfo::getLoginState()
{
    return State;
}

void ClientInfo::setUid(long id)
{
    uid=id;
    refresh();
}

QPixmap ClientInfo::getAvatar() const
{
    return Avatar;
}

void ClientInfo::setAvatar(const QPixmap &value)
{
    Avatar = value;
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

    connect(&NAM,&QNetworkAccessManager::finished,this,&ClientInfo::getAvatar);
}

void ClientInfo::setClientInfo(QNetworkReply *reply)
{
    QByteArray raw=reply->readAll();
    QJsonObject JObj=QJsonDocument::fromJson(raw).object();
    Name=JObj["Name"].toString();
    Nickname=JObj["Nickname"].toString();
    Avatar.loadFromData(QByteArray::fromBase64(JObj["Avatar"].toString().toLocal8Bit()));
    emit finished();
}
