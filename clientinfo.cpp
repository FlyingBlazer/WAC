#include "clientinfo.h"
#include "clientinfocollector.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QMessageBox>
#include <QDir>
#include <QUrl>

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
    Instance->commit();
    return Instance;
}

ClientInfo::ClientInfo(QObject *parent) :
    QObject(parent),setting("buaa.GBK","WAC")
{
    State=NotLogin;
    Nickname="undefined";
    SelectedCarId=-1;
    read();
}
int ClientInfo::getSelectedCarId() const
{
    return SelectedCarId;
}

void ClientInfo::setSelectedCarId(int value)
{
    SelectedCarId = value;
}


int ClientInfo::getAge() const
{
    return Age;
}

void ClientInfo::setAge(int value)
{
    Age = value;
}

int ClientInfo::getExpense() const
{
    return Expense;
}

void ClientInfo::setExpense(int value)
{
    Expense = value;
}

bool ClientInfo::getGender() const
{
    return Gender;
}

void ClientInfo::setGender(const bool &value)
{
    Gender = value;
}

int ClientInfo::getIncome() const
{
    return Income;
}

void ClientInfo::setIncome(const int &value)
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

void ClientInfo::commit()
{
    save();
    upLoad();
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
    Gender=JObj["Gender"].toBool();
    Income=JObj["Income"].toInt();
    Education=JObj["Education"].toString();
    Age=JObj["Age"].toInt();
    if(JObj.contains("SelectedCar"))
        SelectedCarId=JObj["SelectedCar"].toInt();

    emit finished();
}

void ClientInfo::upLoad()
{
    QNetworkAccessManager NAM;
    QNetworkRequest request(QUrl(Settings::ClientInfoUpLoadPage));
    request.setRawHeader("Content-Type","application/x-www-form-urlencoded");
    QByteArray postData;
    postData.append("token=").append(Token)
            .append("&Nickname=").append(Nickname)
            .append("&Gender=").append(Gender)
            .append("&Income=").append(Income)
            .append("&Education=").append(Education)
            .append("&Age=").append(Age);
    NAM.post(request,QUrl(postData).toEncoded());
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
        Gender=setting.value("Gender").toBool();
        Income=setting.value("Income").toInt();
        Education=setting.value("Education").toString();
        Age=setting.value("Age").toInt();
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
    setting.setValue("Gender",Gender);
    setting.setValue("Income",Income);
    setting.setValue("Education",Education);
    setting.endGroup();
}

void ClientInfo::inputClientInfo()
{
    ClientInfoCollector cic;
    connect(&cic,&ClientInfoCollector::data,[this](QString nickname,bool Gender,int income,QString education,int age){
        Nickname=nickname;
        Gender=Gender;
        Income=income;
        Education=education;
        Age=age;
    });
    cic.exec();
}
