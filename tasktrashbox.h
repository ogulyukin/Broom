#ifndef TASKTRASHBOX_H
#define TASKTRASHBOX_H
#include <windows.h>
#include <shellapi.h>
#include <QThread>
#include "taskobject.h"

class TaskTrashBox : public TaskObject
{
    Q_OBJECT
public:
    explicit TaskTrashBox(QCheckBox* cb, QLabel* lab, QString path = "", QObject *parent = nullptr);
    void run();
};

#endif // TASKTRASHBOX_H
