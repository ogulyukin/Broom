#include <QJsonDocument>
#include <QFile>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>
#include <QBitArray>
#include "configloader.h"

QMap<QString, QString>* ConfigLoader::readConfig(QString path)
{
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Не открывается файл конфигурации для чтения!";
        return nullptr;
    }
    QByteArray data = file.readAll();
    file.close();
    QJsonDocument document = QJsonDocument::fromJson(data);
    QVariantMap tempMap = qvariant_cast<QVariantMap>(document["Directories"]);
    QMap<QString, QString>* map = new QMap<QString, QString>;
    for (auto it = tempMap.begin(); it != tempMap.end(); it++)
    {
        map->insert(it.key(), getPath(it.value().toString()));
    }
    return map;
}

QString ConfigLoader::getPath(QString path)
{
    if(path.startsWith("%homepath%") || path.startsWith("%HOMEPATH%"))
    {
        //path = qEnvironmentVariable("HOMEPATH") + path.remove(0, 10);
        path = QDir::homePath() + path.remove(0, 10);
    }
    if(path.startsWith("%systeroot%"))
    {
        path = qEnvironmentVariable("SYSTEMROOT") + path.remove(0, 11);
    }
    //qDebug() << path;
    return path;
}
