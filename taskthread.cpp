#include "taskthread.h"

TaskThread::TaskThread(TaskObject* tobj) : QRunnable(), tobj(tobj)
{

}

void TaskThread::run()
{
    tobj->run();
}
