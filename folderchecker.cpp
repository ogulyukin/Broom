#include "folderchecker.h"
#include <QFile>
#include <QDebug>

void FolderChecker::isExistDir(QCheckBox* cb, QString path, DirInfo &DI)
{
    QDir *dir = new QDir(path);
    if(!dir->exists(path) && !path.contains("$RECYCLE.BIN"))
    {
        cb->setDisabled(true);
        delete dir;
        return;
    }
    DI.size = 0;
    DI.dirC = 0;
    DI.allItem = dir->count();
    DI.filesC = fileCountsCollector(path, DI.dirC, DI.size);
    delete dir;
    return;
}

void FolderChecker::deleteFiles(QString path)
{
    emit sendMsg("ИНФО", "Удаление", "Начинаем удаление файлов:");
    deleteTargets(path, path);
    emit sendMsg("ИНФО", "Удаление", "Удаление файлов завершено");
}

void FolderChecker::run()
{
    if(path.contains("$RECYCLE.BIN"))
    {
        emit sendMsg("УСПЕХ","Удаление", QThread::currentThread()->objectName() + "Очистка Корзины");
        SHEmptyRecycleBin(0,0,SHERB_NOCONFIRMATION | SHERB_NOPROGRESSUI | SHERB_NOSOUND);
        return;
    }
    emit sendMsg("ИНФО", "Удаление", QThread::currentThread()->objectName() + " Начинаем удаление файлов:");
    deleteTargets(path, path);
    emit sendMsg("ИНФО", "Удаление", QThread::currentThread()->objectName() + " Удаление файлов завершено");
}

int FolderChecker::fileCountsCollector(QString path, int &dirC, int &sizeC)
{
    QDir *dir = new QDir(path);
    QList<QFileInfo> fileList = dir->entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries | QDir::Hidden);
    QList<QFileInfo>::iterator it = fileList.begin();
    int result = 0;
    for(; it != fileList.end(); it++)
    {
        if(it->isDir())
        {
            result += fileCountsCollector(it->absoluteFilePath(), dirC, sizeC);
            dirC++;
        }else if(it->isFile())
        {
            result++;
            sizeC += it->size();
        }
    }
    delete dir;
    return result;
}

void FolderChecker::deleteTargets(QString path, QString ignore)
{
    QDir *dir = new QDir(path);
    QFileInfoList list = dir->entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries | QDir::Hidden);
    QFileInfoList::iterator it = list.begin();
    for (; it != list.end(); it++)
    {
        qDebug() << it->absoluteFilePath();
        if(it->isDir() && it->exists())
        {
            deleteTargets(it->absoluteFilePath(), ignore);
        }else if(it->exists())
        {
            QFile::setPermissions(it->absoluteFilePath(), QFile::ReadOwner | QFile::WriteOwner);
            QFile::remove(it->absoluteFilePath());
            printResult(*it);
        }
    }
    if(path != ignore && dir->exists(path))
    {
        dir->rmdir(path);
        if(!dir->exists(path))
        {
           //qDebug() << "SUCESS deletion: " << path;
            emit sendMsg("УСПЕХ","Удаление", path);
        }else
        {
           //qDebug() << "ERROR: deletion: " << path;
            emit sendMsg("ОШИБКА","Удаление", path);
        }
        emit deleted();
    }
    delete dir;
}

void FolderChecker::printResult(QFileInfo &it)
{
    if(!QFile::exists(it.absoluteFilePath()))
    {
       //qDebug() << "Secces deletion: " << it.absoluteFilePath();
        emit sendMsg("УСПЕХ","Удаление",it.absoluteFilePath());
    }else
    {
       //qDebug() << "Error deletion: " << it.absoluteFilePath();
        emit sendMsg("ОШИБКА","Удаление",it.absoluteFilePath());
    }
    emit deleted();
}

FolderChecker::FolderChecker(QString path, QObject *parent): QObject(parent), QRunnable(), path(path)
{

}

