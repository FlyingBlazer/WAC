#include "utils.h"

#ifndef WINVER
#include <QAndroidJniObject>
#include <QtAndroid>
#endif

QString getExternalStorageDirectory()
{
#ifndef WINVER
    QAndroidJniObject File=QAndroidJniObject::callStaticObjectMethod(
            "android/os/Environment","getExternalStorageDirectory",
            "()Ljava/io/File;");
    QAndroidJniObject Dir=File.callObjectMethod("toString","()Ljava/lang/String;");
    return Dir.toString();
#else
    return QString();
#endif
}

void share(QString str)
{
#ifndef WINVER
    QAndroidJniObject intent("android/content/Intent");
    intent.callObjectMethod("addAction","(Ljava/lang/String;)Landroid/content/Intent;",
                            QAndroidJniObject::fromString("android.intent.action.VIEW"));
    intent.callObjectMethod("setType","(Ljava/lang/String;)Landroid/content/Intent;",
                            QAndroidJniObject::fromString("image/*"));
    intent.callObjectMethod("putExtra","(Ljava/lang/String;Ljava/lang/string;)Landroid/content/Intent;",
                            QAndroidJniObject::fromString("android.intent.extra.SUBJECT"),QAndroidJniObject::fromString("分享"));
    intent.callObjectMethod("putExtra","(Ljava/lang/String;Ljava/lang/string;)Landroid/content/Intent;",
                            QAndroidJniObject::fromString("android.intent.extra.TEXT"),QAndroidJniObject::fromString(str));
    intent.callObjectMethod("setFlags","(I)Landroid/content/Intent;",268435456);
    QAndroidJniObject intent2 =
            intent.callObjectMethod("createChooser","(Landroid/content/Intent;Ljava/lang/CharSequence;)Landroid/content/Intent;",
                                    intent,"Share");
    QtAndroid::startActivity(intent,123456);
#else
    return;
#endif
}
