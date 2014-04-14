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
    explicit ClientInfo(QObject *parent = 0);

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

    QPixmap getAvatar() const;
    void setAvatar(const QPixmap &value);

    QString getToken() const;
    void setToken(const QString &value);

public slots:
    void refresh();
    void setUid(long);

signals:
    void finished();

private:
    LoginState State;

    long uid;
    QString Name;
    QString Nickname;
    QString Token;
    QPixmap Avatar;
    QByteArray AvatarBase64;

    QFile Data;

    void saveToFile();
    void readFromFile();

private slots:
    void setClientInfo(QNetworkReply *);
};

#endif // CLIENTINFO_H
