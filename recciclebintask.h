#ifndef RECCICLEBINTASK_H
#define RECCICLEBINTASK_H
#include <windows.h>
#include <shellapi.h>
#include <QThread>
#include "taskobject.h"

class RecicleBinTask : public TaskObject
{
    Q_OBJECT
public:
    explicit RecicleBinTask(QCheckBox* cb, QLabel* lab, QString path = "", QObject *parent = nullptr);
    void run();
};

#endif // RECCICLEBINTASK_H
