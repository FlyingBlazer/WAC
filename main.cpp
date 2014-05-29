#include "mainwindow.h"
#include "clientinfo.h"
#include "clientinfocollector.h"
#include "login.h"
#include <QApplication>

bool checkLoginState()
{
    ClientInfo *client=ClientInfo::getInstance();
    return client->getLoginState()==ClientInfo::HasLogin;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if(!checkLoginState())
    {
        Login login;
        login.exec();
    }
    if(!checkLoginState()) a.quit();
    MainWindow mw;
    mw.show();
    return a.exec();
}
