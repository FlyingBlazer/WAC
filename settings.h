#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>

class Settings
{
public:
    Settings();

    static QString Domain;
    static QString LoginPage;
    static QString LogoutPage;
    static QString SignPage;
    static QString ClientInfoPage;
    static QString ClientInfoUpLoadPage;
    static QString CarDetailpage;
    static QString RecommandCar;
    static QString CarlistPage;
    static QString getSelectedCar;
    static QString setSelectedCar;
};

#endif // SETTINGS_H
