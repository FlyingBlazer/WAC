#include "clientinfo.h"
#include "clientinfocollector.h"
#include "priceattention.h"
#include <QEventLoop>
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
    Instance->State=HasLogin;
    Instance->Name=username;
    Instance->Email=email;
    Instance->Token=token;
    if(fromSign)
        Instance->inputClientInfo();
    else
        Instance->refresh();
    return Instance;
}

ClientInfo::ClientInfo(QObject *parent) :
    QObject(parent),setting("buaa.GBK","WAC")
{
    State=NotLogin;
    Nickname="undefined";
    SelectedCarId=-1;
    SelectedCarPrice=-1.0;
    read();
    if(State==HasLogin)
    {
        QNetworkAccessManager nnn;
        QNetworkRequest req(QUrl(Settings::ClientInfoPage));
        QByteArray data;
        data.append("username=").append(Name).append("&token=").append(Token);
        QNetworkReply *reply=nnn.post(req,data);
        QEventLoop loop;
        connect(reply,&QNetworkReply::finished,[&loop](){
            loop.exit();
        });
        loop.exec();
        QJsonObject JObj=QJsonDocument::fromJson(reply->readAll()).object();
        if(JObj["status"]!="ok") {
            State=NotLogin;
        } else {
            refresh();
        }
    }
    connect(this,&ClientInfo::finished,this,&ClientInfo::check);
    connect(&NAM,&QNetworkAccessManager::finished,this,&ClientInfo::getClientInfo);
    connect(&NAM,&QNetworkAccessManager::finished,this,&ClientInfo::setSelectedCar);
    connect(&NAM,&QNetworkAccessManager::finished,this,&ClientInfo::setSelectedCarInfo);
}

double ClientInfo::getLastSelectedCarPrice() const
{
    return lastSelectedCarPrice;
}

void ClientInfo::setLastSelectedCarPrice(double value)
{
    lastSelectedCarPrice = value;
}

int ClientInfo::getBalance() const
{
    return Balance;
}

void ClientInfo::setBalance(int value)
{
    Balance = value;
}

double ClientInfo::getSelectedCarPrice() const
{
    return SelectedCarPrice;
}

void ClientInfo::setSelectedCarPrice(double value)
{
    SelectedCarPrice = value;
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

void ClientInfo::check()
{
    if(Education.isEmpty())
    {
        inputClientInfo();
    }
}

void ClientInfo::income(int inc)
{
    Balance+=inc;
    commit();
}

void ClientInfo::refresh()
{
    QNetworkRequest request1(QUrl(Settings::ClientInfoPage));
    request1.setRawHeader("Content-Type","application/x-www-form-urlencoded");
    QByteArray postData1;
    postData1.append("token=").append(Token).append("&username=").append(Name);
    postData1=QUrl(postData1).toEncoded();
    NAM.post(request1,postData1);
    QNetworkRequest request2(QUrl(Settings::getSelectedCar));
    request2.setRawHeader("Content-Type","application/x-www-form-urlencoded");
    QByteArray postData2;
    postData2.append("token=").append(Token).append("&username=").append(Name);
    postData2=QUrl(postData2).toEncoded();
    NAM.post(request2,postData2);
}

void ClientInfo::getClientInfo(QNetworkReply *reply)
{
    if(reply->request().url().toString().compare(Settings::ClientInfoPage)!=0)
        return;
    QByteArray raw=reply->readAll();
    QJsonObject JObj=QJsonDocument::fromJson(raw).object();
    if(JObj["status"].toString()=="fail")
    {
        QMessageBox::warning(0,QString("错误"),JObj["msg"].toString());
        return;
    }
    Email=JObj["email"].toString();
    Nickname=JObj["nickname"].toString();
    Gender=JObj["gender"].toBool();
    Income=JObj["income"].toInt();
    Education=JObj["education"].toString();
    Age=JObj["age"].toInt();
    Balance=JObj["balance"].toInt();
    save();
    emit finished();
}

void ClientInfo::setSelectedCar(QNetworkReply *reply)
{
    if(reply->request().url().toString().compare(Settings::getSelectedCar)!=0)
        return;
    QByteArray raw=reply->readAll();
    QJsonObject JObj=QJsonDocument::fromJson(raw).object();
    if(JObj["status"].toString()=="fail")
    {
        QMessageBox::warning(0,QString("错误"),JObj["msg"].toString());
        return;
    }
    SelectedCarId=JObj["target"].toInt();
    QNetworkRequest request3(QUrl(Settings::CarDetailpage));
    request3.setRawHeader("Content-Type","application/x-www-form-urlencoded");
    QByteArray postData3;
    postData3.append("id=").append(QString::number(SelectedCarId));
    postData3=QUrl(postData3).toEncoded();
    NAM.post(request3,postData3);
}

void ClientInfo::setSelectedCarInfo(QNetworkReply *reply)
{
    lastSelectedCarPrice=SelectedCarPrice;
    if(reply->request().url().toString().compare(Settings::CarDetailpage)!=0)
        return;
    QByteArray raw=reply->readAll();
    QJsonObject JObj=QJsonDocument::fromJson(raw).object();
    if(JObj["status"].toString()=="fail")
    {
        QMessageBox::warning(0,QString("错误"),JObj["msg"].toString());
        return;
    }
    SelectedCarPrice=JObj["info"].toObject().value("price").toDouble();
    save();
    emit infogot();
    if(lastSelectedCarPrice>0 && lastSelectedCarPrice<SelectedCarPrice) {
        PriceAttention pa((int)((SelectedCarPrice-lastSelectedCarPrice)*10000));
        pa.exec();
    }
}

void ClientInfo::upLoad()
{
    QNetworkRequest request1(QUrl(Settings::ClientInfoUpLoadPage));
    request1.setRawHeader("Content-Type","application/x-www-form-urlencoded");
    QByteArray postData1;
    postData1.append("token=").append(Token)
            .append("&username=").append(Name)
            .append("&nickname=").append(Nickname)
            .append("&gender=").append(Gender?"1":"0")
            .append("&income=").append(QString::number(Income))
            .append("&balance=").append(QString::number(Balance))
            .append("&expense=").append("0")
            .append("&education=").append(Education)
            .append("&age=").append(QString::number(Age));
    postData1=QUrl(postData1).toEncoded();
    NAM.post(request1,postData1);
    QNetworkRequest request2(QUrl(Settings::setSelectedCar));
    request2.setRawHeader("Content-Type","application/x-www-form-urlencoded");
    QByteArray postData2;
    postData2.append("token=").append(Token)
            .append("&username=").append(Name)
            .append("&target=").append(QString::number(SelectedCarId));
    postData2=QUrl(postData2).toEncoded();
    NAM.post(request2,postData2);

    refresh();
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
        Balance=setting.value("Balance").toInt();
        Education=setting.value("Education").toString();
        Age=setting.value("Age").toInt();
        SelectedCarId=setting.value("SelectedCarId").toInt();
        SelectedCarPrice=setting.value("SelectedCarPrice").toDouble();
        State=HasLogin;
    }
    setting.endGroup();
}

void ClientInfo::save()
{
    setting.beginGroup("ClientInfo");
    setting.setValue("Name",Name);
    setting.setValue("Age",Age);
    setting.setValue("Email",Email);
    setting.setValue("Nickname",Nickname);
    setting.setValue("Token",Token);
    setting.setValue("Balance",Balance);
    setting.setValue("Gender",Gender);
    setting.setValue("Income",Income);
    setting.setValue("Education",Education);
    setting.setValue("SelectedCarId",SelectedCarId);
    setting.setValue("SelectedCarPrice",SelectedCarPrice);
    setting.endGroup();
}

void ClientInfo::inputClientInfo()
{
    ClientInfoCollector cic;
    connect(&cic,&ClientInfoCollector::data,this,&ClientInfo::setInfo);
    cic.exec();
}

void ClientInfo::setInfo(QString nickname,bool gender,int income,QString education,int age)
{
    Nickname=nickname;
    Gender=gender;
    Income=income;
    Education=education;
    Age=age;
    Balance=0;
    commit();
}

void ClientInfo::selectCar(int id)
{
    SelectedCarId=id;
    commit();
}
