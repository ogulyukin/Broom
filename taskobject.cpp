#include "taskobject.h"

TaskObject::TaskObject(QCheckBox *cb, QLabel *lab, QString path, QObject *parent) :QObject(parent)
{
    this->cb = cb;
    this->lab = lab;
    elements = 0;
    this->path = path;
}

bool TaskObject::isCheckboxChecked()
{
    if(cb->isChecked())
        return true;
    return false;
}

bool TaskObject::isCheckboxEnabled()
{
    return cb->isEnabled();
}

void TaskObject::setCheckBoxChecked()
{
    cb->setChecked(true);
}

void TaskObject::setCheckBoxUnchecked()
{
    cb->setChecked(false);
}

void TaskObject::seLabelText(QString text)
{
    lab->setText(text);
}

int TaskObject::getElements()
{
    return elements;
}

void TaskObject::emitResult(QFileInfo &it)
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

void TaskObject::dirInfoCollector(QString path, int &fileC, int &dirC, int &sizeC)
{
    QDir *dir = new QDir(path);
    QFileInfoList fileList = dir->entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries | QDir::Hidden);
    for(auto it = fileList.begin(); it != fileList.end(); it++)
    {
        if(it->isDir())
        {
            dirInfoCollector(it->absoluteFilePath(), fileC, dirC, sizeC);
            dirC++;
        }else if(it->isFile())
        {
            fileC++;
            sizeC += it->size();
        }
    }
    delete dir;
    fileList.clear();
}

void TaskObject::clearDirectory(QString path, QString ignore)
{
    QDir *dir = new QDir(path);
    QFileInfoList list = dir->entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries | QDir::Hidden);
    QFileInfoList::iterator it = list.begin();
    for (; it != list.end(); it++)
    {
        qDebug() << it->absoluteFilePath();
        if(it->isDir() && it->exists())
        {
            clearDirectory(it->absoluteFilePath(), ignore);
        }else if(it->exists())
        {
            QFile::setPermissions(it->absoluteFilePath(), QFile::ReadOwner | QFile::WriteOwner);
            QFile::remove(it->absoluteFilePath());
            emitResult(*it);
        }
    }
    if(path != ignore && dir->exists(path))
    {
        removeDirectory(path);
    }
    delete dir;
}

void TaskObject::removeDirectory(QString path)
{
    QDir *dir = new QDir(path);
    dir->rmdir(path);
    if(!dir->exists(path))
    {
        emit sendMsg("УСПЕХ","Удаление", path);
    }else
    {
        emit sendMsg("ОШИБКА","Удаление", path);
    }
    emit deleted();
    delete dir;
}


