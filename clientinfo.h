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

public slots:
    void refresh();

signals:
    void finished();

private:
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

    QFile Data;

    void save();
    void read();
    void upLoad();
    void inputClientInfo();

private slots:
    void setClientInfo(QNetworkReply *);
};

#endif // CLIENTINFO_H
