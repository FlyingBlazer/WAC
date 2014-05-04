#ifndef CLIENTINFO_H
#define CLIENTINFO_H

#include "settings.h"
#include "utils.h"
#include <QObject>
#include <QPixmap>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>

class ClientInfo : public QObject
{
    Q_OBJECT
public:
    static ClientInfo &getInstance();
    static ClientInfo &newClient(QString username,QString email,QString token);

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

    QByteArray getAvatarBase64() const;
    void setAvatarBase64(const QByteArray &value);

public slots:
    void refresh();
    void setUid(long);

signals:
    void finished();

private:
    static ClientInfo Instance;

    ClientInfo(QObject *parent = 0);

    LoginState State;

    long uid;
    QString Name;
    QString Nickname;
    QString Email;
    QString Token;
    QByteArray AvatarBase64;

    QFile Data;

    void saveToFile();
    void readFromFile();
    void inputClientInfo();

private slots:
    void setClientInfo(QNetworkReply *);
};

#endif // CLIENTINFO_H
