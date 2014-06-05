#include "settings.h"

QString Settings::Domain="https://wac-wantacar.rhcloud.com";

QString Settings::LoginPage=Settings::Domain+"/login";

QString Settings::LogoutPage=Settings::Domain+"/logout";

QString Settings::SignPage=Settings::Domain+"/register";

QString Settings::ClientInfoPage=Settings::Domain+"/getinfo";

QString Settings::ClientInfoUpLoadPage=Settings::Domain+"/setinfo";

QString Settings::CarDetailpage=Settings::Domain+"/getcarinfo";

QString Settings::RecommandCar=Settings::Domain+"/getsuggestion";

QString Settings::CarlistPage=Settings::Domain+"/getallcars";

QString Settings::getSelectedCar=Settings::Domain+"/gettarget";

QString Settings::setSelectedCar=Settings::Domain+"/settarget";
