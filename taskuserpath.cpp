#include "taskuserpath.h"

TaskUserPAth::TaskUserPAth(QCheckBox* cb, QLabel* lab, QString path, QObject *parent) : TaskObject(cb, lab, path, parent)
{
    if(isExistPath())
    {
       DirInfo* DI = new DirInfo();
       dirInfoCollector(path, DI->filesC, DI->dirC, DI->size);
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

void TaskUserPAth::run()
{
    emit sendMsg("ИНФО", "Удаление", QThread::currentThread()->objectName() + " Начинаем удаление файлов:");
    clearDirectory(path, path);
    DirInfo* DI = new DirInfo();
    dirInfoCollector(path, DI->filesC, DI->dirC, DI->size);
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
    emit finished();
}

bool TaskUserPAth::isExistPath()
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



