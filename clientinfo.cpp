#include "clientinfo.h"
#include "clientinfocollector.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QMessageBox>
#include <QDir>

ClientInfo *ClientInfo::Instance=0;

ClientInfo *ClientInfo::getInstance(QObject *parent)
{
    if(Instance!=0)
        return Instance;
    else
        return (Instance=new ClientInfo(parent));
}

ClientInfo *ClientInfo::newClient(QString username, QString email, QString token, bool fromSign, QObject *parent)
{
    if(Instance!=0)
        delete Instance;
    Instance=new ClientInfo(parent);
    Instance->Name=username;
    Instance->Email=email;
    Instance->Token=token;
    if(fromSign)
        Instance->inputClientInfo();
    else
        Instance->refresh();
    Instance->save();
    Instance->upLoad();
    return Instance;
}

ClientInfo::ClientInfo(QObject *parent) :
    QObject(parent),setting("buaa.GBK","WAC")
{
    State=NotLogin;
    read();
}

QString ClientInfo::getSex() const
{
    return Sex;
}

void ClientInfo::setSex(const QString &value)
{
    Sex = value;
}

QString ClientInfo::getIncome() const
{
    return Income;
}

void ClientInfo::setIncome(const QString &value)
{
    Income = value;
}

QString ClientInfo::getEducation() const
{
    return Education;
}

void ClientInfo::setEducation(const QString &value)
{
    Education = value;
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
    QByteArray postData;
    postData.append("token=").append(Token)
            .append("&magic=").append(Settings::Magic);
    NAM.post(request,postData);

    connect(&NAM,&QNetworkAccessManager::finished,this,&ClientInfo::setClientInfo);
}

void ClientInfo::setClientInfo(QNetworkReply *reply)
{
    QByteArray raw=reply->readAll();
    QJsonObject JObj=QJsonDocument::fromJson(raw).object();
    Email=JObj["Email"].toString();
    Nickname=JObj["Nickname"].toString();
    Sex=JObj["Sex"].toString();
    Income=JObj["Income"].toString();
    Education=JObj["Education"].toString();
    emit finished();
}

void ClientInfo::upLoad()
{
    QJsonObject JObj;
    JObj.insert("Nickname",Nickname);
    JObj.insert("Sex",Sex);
    JObj.insert("Income",Income);
    JObj.insert("Education",Education);
    QByteArray data=QJsonDocument(JObj).toJson();
    QNetworkAccessManager NAM;
    QNetworkRequest request(QUrl(Settings::ClientInfoUpLoadPage));
    request.setRawHeader("Content-Type","application/x-www-form-urlencoded");
    QByteArray postData;
    postData.append("token=").append(Token)
            .append("&Nickname=").append(Nickname)
            .append("&Sex=").append(Sex)
            .append("&Income=").append(Income)
            .append("&Education=").append(Education);
    NAM.post(request,postData);
}

void ClientInfo::read()
{
    setting.beginGroup("ClientInfo");
    if(setting.contains("Token"))
    {
        Name=setting.value("Name").toString();
        Email=setting.value("Email").toString();
        Nickname=setting.value("Nickname").toString();
        Token=setting.value("Token").toString();
        Sex=setting.value("Sex").toString();
        Income=setting.value("Income").toString();
        Education=setting.value("Education").toString();
        State=HasLogin;
    }
    setting.endGroup();
}

void ClientInfo::save()
{
    setting.beginGroup("ClientInfo");
    setting.setValue("Name",Name);
    setting.setValue("Email",Email);
    setting.setValue("Nickname",Nickname);
    setting.setValue("Token",Token);
    setting.setValue("Sex",Sex);
    setting.setValue("Income",Income);
    setting.setValue("Education",Education);
    setting.endGroup();
}

void ClientInfo::inputClientInfo()
{
    ClientInfoCollector cic;
    connect(&cic,&ClientInfoCollector::data,[this](QString nickname,QString sex,QString income,QString education){
        Nickname=nickname;
        Sex=sex;
        Income=income;
        Education=education;
    });
    cic.exec();
}
