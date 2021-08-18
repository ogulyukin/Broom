#include "taskobject.h"

TaskObject::TaskObject(QCheckBox *cb, QLabel *lab, QString path, QObject *parent) :QObject(parent), QRunnable()
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


