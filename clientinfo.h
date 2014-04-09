#ifndef CLIENTINFO_H
#define CLIENTINFO_H

#include "settings.h"
#include <QObject>
#include <QPixmap>
#include <QNetworkAccessManager>
#include <QNetworkReply>

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
    QPixmap Avatar;

private slots:
    void setClientInfo(QNetworkReply *);
};

#endif // CLIENTINFO_H