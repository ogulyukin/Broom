#include "taskmozilla.h"

taskMozilla::taskMozilla(QCheckBox* cb, QLabel* lab, QString path, QObject *parent) : TaskObject(cb, lab, path, parent)
{
    QString tempPath = ConfigLoader::getPath("%homepath%\\AppData\\Local\\Mozilla\\Firefox\\Profiles");
    QDir *dir = new QDir(tempPath);
    if(dir->exists(tempPath))
    {
        this->path = findRightPath(dir);
        DirInfo* DI = new DirInfo();
        if (this->path != "")
        {
             dirInfoCollector(this->path, DI->filesC, DI->dirC, DI->size);
        }
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
    }else
    {
        lab->setText("Нечего удалять");
        cb->setDisabled(true);
    }
    delete dir;
}

QString taskMozilla::findRightPath(QDir *dir)
{
    QFileInfoList list = dir->entryInfoList(QDir::NoDotAndDotDot | QDir::Dirs);
    for (auto i = list.begin(); i != list.end(); i++)
    {
        QString tempPath = i->absoluteFilePath() + QDir::separator() + "cache2" + QDir::separator() + "entries";
        QDir *tempDir = new QDir(tempPath);
        if (tempDir->exists(tempPath))
        {
            delete tempDir;
            return tempPath;
        }
        delete tempDir;
    }
    return "";
}

void taskMozilla::run()
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
