#include "utils.h"

#ifndef WINVER
#include <QAndroidJniObject>
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
