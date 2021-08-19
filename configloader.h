#ifndef CONFIGLOADER_H
#define CONFIGLOADER_H
#include <QMap>
#include <QString>
#include <QStringList>

class ConfigLoader
{
public:
    static QMap<QString, QString>* readConfig(QString path);
    static QString getPath(QString path);
};

#endif // CONFIGLOADER_H
