#ifndef TASKUSERPATH_H
#define TASKUSERPATH_H

#include "taskobject.h"

class TaskUserPAth : public TaskObject
{
    Q_OBJECT
public:
    explicit TaskUserPAth(QCheckBox* cb, QLabel* lab, QString path = "", QObject *parent = nullptr);
    void run();

private:
    bool isExistPath();
};

#endif // TASKUSERPATH_H
