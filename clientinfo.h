#ifndef CLIENTINFO_H
#define CLIENTINFO_H

#include "settings.h"
#include "utils.h"
#include <QObject>
#include <QPixmap>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include <QSettings>

class ClientInfo : public QObject
{
    Q_OBJECT
public:
    static ClientInfo *getInstance(QObject *parent=0);
    static ClientInfo *newClient(QString username, QString email, QString token, bool fromSign=0, QObject *parent=0);

    enum LoginState
    {
        NotLogin,
        HasLogin,
        LoginOutOfDate
    };
    LoginState getLoginState();

    QString getName() const;
    void setName(const QString &value);

    QString getNickname() const;
    void setNickname(const QString &value);

    QString getToken() const;
    void setToken(const QString &value);

    QString getEmail() const;
    void setEmail(const QString &value);

    QString getEducation() const;
    void setEducation(const QString &value);

    int getIncome() const;
    void setIncome(const int &value);

    bool getGender() const;
    void setGender(const bool &value);

    int getExpense() const;
    void setExpense(int value);

    int getAge() const;
    void setAge(int value);

    void commit();

    int getSelectedCarId() const;
    void setSelectedCarId(int value);

    double getSelectedCarPrice() const;
    void setSelectedCarPrice(double value);

    void check();
    void income(int);

    int getBalance() const;
    void setBalance(int value);

    double getLastSelectedCarPrice() const;
    void setLastSelectedCarPrice(double value);

public slots:
    void refresh();
    void selectCar(int);

signals:
    void finished();
    void infogot();

private:
    QNetworkAccessManager NAM;
    static ClientInfo *Instance;

    ClientInfo(QObject *parent = 0);

    LoginState State;
    QSettings setting;

    QString Name;
    QString Nickname;
    QString Email;
    QString Token;
    QString Education;
    bool Gender;
    int Income;
    int Age;
    int Expense;
    int SelectedCarId;
    double SelectedCarPrice;
    double lastSelectedCarPrice;
    int Balance;

    QFile Data;

    void save();
    void read();
    void upLoad();
    void inputClientInfo();

private slots:
    void getClientInfo(QNetworkReply *);
    void setInfo(QString nickname,bool gender,int income,QString education,int age);
    void setSelectedCar(QNetworkReply *);
    void setSelectedCarInfo(QNetworkReply *);
};

#endif // CLIENTINFO_H
