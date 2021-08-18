#include "userpathtask.h"

UserPAthTask::UserPAthTask(QCheckBox* cb, QLabel* lab, QString path, QObject *parent) : TaskObject(cb, lab, path, parent)
{
    if(isExistDir())
    {
       DirInfo* DI = new DirInfo();
       DI->filesC = fileCountsCollector(path, DI->dirC, DI->size);
       if(DI->dirC == 0 && DI->filesC == 0)
       {
           lab->setText("Нечего удалять");
           cb->setDisabled(true);
       }else
       {
           lab->setText("Найдено " + QString::number(DI->filesC) + " файлов, " + QString::number(DI->dirC) + " папок, " + QString::number(DI->size/1024/1024) + " Мб");
       }
       elements = DI->filesC + DI->dirC;
       delete  DI;
    }
}

void UserPAthTask::run()
{
    emit sendMsg("ИНФО", "Удаление", QThread::currentThread()->objectName() + " Начинаем удаление файлов:");
    deleteTargets(path, path);
    DirInfo* DI = new DirInfo();
    DI->filesC = fileCountsCollector(path, DI->dirC, DI->size);
    if(DI->dirC == 0 && DI->filesC == 0)
    {
        lab->setText("Нечего удалять");
        cb->setDisabled(true);
    }else
    {
        lab->setText("Найдено " + QString::number(DI->filesC) + " файлов, " + QString::number(DI->dirC) + " папок, " + QString::number(DI->size/1024/1024) + " Мб");
    }
    cb->setChecked(false);
    elements = DI->filesC + DI->dirC;
    delete  DI;
    emit sendMsg("ИНФО", "Удаление", QThread::currentThread()->objectName() + " Удаление файлов завершено");
}

int UserPAthTask::fileCountsCollector(QString path, int &dirC, int &sizeC)
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

void UserPAthTask::deleteTargets(QString path, QString ignore)
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
            emit sendMsg("УСПЕХ","Удаление", path);
        }else
        {
            emit sendMsg("ОШИБКА","Удаление", path);
        }
        emit deleted();
    }
    delete dir;
}

void UserPAthTask::printResult(QFileInfo &it)
{
    if(!QFile::exists(it.absoluteFilePath()))
    {
        emit sendMsg("УСПЕХ","Удаление",it.absoluteFilePath());
    }else
    {
        emit sendMsg("ОШИБКА","Удаление",it.absoluteFilePath());
    }
    emit deleted();
}

bool UserPAthTask::isExistDir()
{
    QDir *dir = new QDir(path);
    if(!dir->exists(path))
    {
        cb->setDisabled(true);
        lab->setText("Нечего удалять");
    }
    delete dir;
    return cb->isEnabled();
}
