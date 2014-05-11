#include "settings.h"

QString Settings::Domain="https://wac-wantacar.rhcloud.com";

QString Settings::LoginPage=Settings::Domain+"/login";

QString Settings::LogoutPage=Settings::Domain+"/logout";

QString Settings::SignPage=Settings::Domain+"/register";

QString Settings::Magic="HowAreYou";

QString Settings::ClientInfoPage=Settings::Domain+"/clientinfo";

QString Settings::ClientInfoUpLoadPage=Settings::ClientInfoPage+"/upload";

QString Settings::CarDetailpage=Settings::Domain+"/cardetail";
