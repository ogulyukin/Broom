#include "folderchecker.h"
#include <QFile>
#include <QDebug>
void FolderChecker::isExistDir(QCheckBox* cb, QString path, DirInfo &DI)
{
    QDir *dir = new QDir(path);
    if(!dir->exists(path))
    {
        cb->setDisabled(true);
        delete dir;
        return;
    }
    //dirInfoCollector(dir, DI);
    DI.size = 0;
    DI.filesC = 0;
    DI.dirC = 0;
    DI.allItem = dir->count();
    DI.filesC += fileCountsCollector(path, DI.dirC, DI.size, DI.allItem);
    //qDebug() << " Найдено: " << DI.filesC << " файлов, " << DI.dirC << " папок." << "Объем: " << DI.size;
    delete dir;
    return;
}

void FolderChecker::deleteFiles(QString path, Logger *log)
{
    log->addEvent("ИНФО", "Удаление", "Начинаем удаление файлов:");
    collectTargets(path, path, log);
    log->addEvent("ИНФО", "Удаление", "Удаление файлов завершено");
}

int FolderChecker::fileCountsCollector(QString path, int &dirC, int &sizeC, int &otherC)
{
    QDir *dir = new QDir(path);
    QList<QFileInfo> fileList = dir->entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries | QDir::Hidden);
    QList<QFileInfo>::iterator it = fileList.begin();
    //getIteratorPos(it);
    int result = 0;
    for(; it != fileList.end(); it++)
    {
        if(it->isDir())
        {
            result += fileCountsCollector(it->absoluteFilePath(), dirC, sizeC, otherC);
            dirC++;
        }else if(it->isFile())
        {
            result++;
            sizeC += it->size();
        }
            otherC += dir->count();
    }
    delete dir;
    return result;
}

void FolderChecker::qListSum(QList<QFileInfo> *list, QList<QFileInfo> *other)
{
    QList<QFileInfo>::iterator it = other->begin();
    for (; it != other->end(); it++)
    {
        list->append(*it);
    }
    delete other;
}

//void FolderChecker::getIteratorPos(QList<QFileInfo>::iterator &it)
//{
//  it++;
//  it++;
//}

void FolderChecker::collectTargets(QString path, QString ignore, Logger *log)
{
    QDir *dir = new QDir(path);
    QFileInfoList list = dir->entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries | QDir::Hidden);
    QFileInfoList::iterator it = list.begin();
    //getIteratorPos(it);
    for (; it != list.end(); it++)
    {
        qDebug() << it->absoluteFilePath();
        if(it->isDir() && it->exists())
        {
            collectTargets(it->absoluteFilePath(), ignore, log);
        }else if(it->exists())
        {
            QFile::setPermissions(it->absoluteFilePath(), QFile::ReadOwner | QFile::WriteOwner);
            QFile::remove(it->absoluteFilePath());
            printResult(*it, log);
        }
    }
    if(path != ignore && dir->exists(path))
    {
        dir->rmdir(path);
        if(!dir->exists(path))
        {
           //qDebug() << "SUCESS deletion: " << path;
            log->addEvent("УСПЕХ","Удаление", path);
        }else
        {
           //qDebug() << "ERROR: deletion: " << path;
            log->addEvent("ОШИБКА","Удаление", path);
        }
    }
    delete dir;
}

void FolderChecker::printResult(QFileInfo &it, Logger *log)
{

    if(!QFile::exists(it.absoluteFilePath()))
    {
       //qDebug() << "Secces deletion: " << it.absoluteFilePath();
        log->addEvent("УСПЕХ","Удаление",it.absoluteFilePath());

    }else
    {
       //qDebug() << "Error deletion: " << it.absoluteFilePath();
        log->addEvent("ОШИБКА","Удаление",it.absoluteFilePath());

    }
}

//FolderChecker::FolderChecker()
//{

//}
