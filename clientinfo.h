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
    static ClientInfo *newClient(QString username, QString email, QString token, QObject *parent=0);

    ClientInfo(ClientInfo&);

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

    QString getIncome() const;
    void setIncome(const QString &value);

    QString getSex() const;
    void setSex(const QString &value);

public slots:
    void refresh();
    void setUid(long);

signals:
    void finished();

private:
    static ClientInfo *Instance;

    ClientInfo(QObject *parent = 0);

    LoginState State;
    QSettings setting;

    long uid;
    QString Name;
    QString Nickname;
    QString Email;
    QString Token;
    QString Sex;
    QString Income;
    QString Education;

    QFile Data;

    void save();
    void read();
    void inputClientInfo();

private slots:
    void setClientInfo(QNetworkReply *);
};

#endif // CLIENTINFO_H
