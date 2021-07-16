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
        //qDebug() << "Не открывается файл конфигурации для чтения!";
        return nullptr;
    }
    //qDebug() << "Begin serialization";
    QByteArray data = file.readAll();
    file.close();
    QJsonDocument document = QJsonDocument::fromJson(data);
    QVariantMap tempMap = qvariant_cast<QVariantMap>(document["Directories"]);
    QMap<QString, QString>* map = new QMap<QString, QString>;
    foreach(QString key, tempMap.keys())
    {
        map->insert(key, getPath(tempMap.value(key).toString()));
    }
    QMap<QString, QString>::Iterator it;
//    for(it = map->begin(); it != map->end(); it++)
//    {
//        qDebug() << "map key: " << it.key() << " map value: " << it.value();
//    }
    return map;

}

void ConfigLoader::writeConfig(QMap<QString, QString> &map, QString path)
{
    QVariantMap finallyMap;
    QVariantMap tempMap;
    foreach(QString key, map.keys())
    {
        tempMap.insert(key, map.value(key));
        qDebug() << "Key: " << key << " value: " << map.value(key);
    }
    finallyMap["Directories"] = QVariant(tempMap);
    QJsonDocument document = QJsonDocument::fromVariant(finallyMap);
    QFile file(path);
    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "Не открывается файл конфигурации для записи!";
        return;
    }
    qDebug() << "Begin serialization";
    file.write(document.toJson());
    qDebug() << file.fileName();
    file.close();
}

QString ConfigLoader::getPath(QString path)
{
    if(path.startsWith("%homepath%") || path.startsWith("%HOMEPATH%"))
    {
        path = qEnvironmentVariable("HOMEPATH") + path.remove(0, 10);
    }
    if(path.startsWith("%systeroot%"))
    {
        path = qEnvironmentVariable("SYSTEMROOT") + path.remove(0, 11);
    }
    return path;
}

ConfigLoader::ConfigLoader()
{

}
