#ifndef CONFIGLOADER_H
#define CONFIGLOADER_H
#include <QMap>
#include <QString>
#include <QStringList>

class ConfigLoader
{
public:
    static QMap<QString, QString>* readConfig(QString path);
    static void writeConfig(QMap<QString, QString> &map, QString path);
    static QString getPath(QString path);
    ConfigLoader();
};

#endif // CONFIGLOADER_H
