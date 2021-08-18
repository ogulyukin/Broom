#ifndef RECICLEBINTASK_H
#define RECICLEBINTASK_H
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

#endif // RECICLEBINTASK_H
