#include "utils.h"

QString getExternalStorageDirectory()
{
    QAndroidJniObject File=QAndroidJniObject::callStaticObjectMethod(
            "android/os/Environment","getExternalStorageDirectory",
            "()Ljava/io/File;");
    QAndroidJniObject Dir=File.callObjectMethod("toString","()Ljava/lang/String;");
    return Dir.toString();
}