#include "settings.h"

QString Settings::Domain="https://wac-wantacar.rhcloud.com";

QString Settings::LoginPage=Settings::Domain+"/login";

QString Settings::LogoutPage=Settings::Domain+"/logout";

QString Settings::SignPage=Settings::Domain+"/register";

QString Settings::Magic="HowAreYou";

QString Settings::ClientInfoPage=Settings::Domain+"/getinfo";

QString Settings::ClientInfoUpLoadPage=Settings::Domain+"/setinfo";

QString Settings::CarDetailpage=Settings::Domain+"/cardetail";

QString Settings::RecommandCar=Settings::Domain+"/getAffordableCars";
