#include "task1c.h"

task1C::task1C(QCheckBox* cb, QLabel* lab, QString path, QObject *parent) : TaskObject(cb, lab, path, parent)
{
    configMap = ConfigLoader::readConfig("config1c.json"); //path stored in value, keys now unused
    collectExistPath();
    countTargets();
}

void task1C::run()
{
    emit sendMsg("ИНФО", "Удаление кеш 1C", QThread::currentThread()->objectName() + " Начинаем удаление файлов:");
    for(auto it = foundPath.begin(); it != foundPath.end(); it++)
    {
        clearDirectory(*it, *it);
        removeDirectory(*it);
    }
    foundPath.clear();
    collectExistPath();
    countTargets();
    emit sendMsg("ИНФО", "Удаление кэш 1C", QThread::currentThread()->objectName() + " Удаление файлов завершено");
}

void task1C::collectExistPath()
{
    for(auto it = configMap->begin(); it != configMap->end(); it++)
    {
        QDir *dir = new QDir(*it);
        if(dir->exists(*it))
        {
            QFileInfoList elementsList = dir->entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries | QDir::Hidden);
            for(auto it2 = elementsList.begin(); it2 != elementsList.end(); it2++)
            {
                if(it2->isDir() && it2->completeBaseName().length() > 30)
                {
                    foundPath.append(it2->absoluteFilePath());
                }
            }
        }
    }
}

void task1C::countTargets()
{
    DirInfo* DI = new DirInfo();
    for(auto it = foundPath.begin(); it != foundPath.end(); it++)
    {
        dirInfoCollector(*it, DI->filesC, DI->dirC, DI->size);
    }
    elements = DI->filesC + DI->dirC;
    if (elements == 0)
    {
        lab->setText("Нечего удалять");
        cb->setDisabled(true);
    }else
    {
        lab->setText("Найдено " + QString::number(DI->filesC) + " файлов, " + QString::number(DI->dirC) + " папок, " + QString::number(DI->size/1024/1024) + " Мб");
    }
    delete  DI;
}


