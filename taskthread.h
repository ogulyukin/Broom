#ifndef TASKTHREAD_H
#define TASKTHREAD_H

#include <QRunnable>
#include "taskobject.h"

class TaskThread : public QRunnable
{
public:
    TaskThread(TaskObject* tobj);
    void run();
private:
    TaskObject* tobj;
};

#endif // TASKTHREAD_H
