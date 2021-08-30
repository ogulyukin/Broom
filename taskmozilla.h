#ifndef TASKMOZILLA_H
#define TASKMOZILLA_H

#include "taskobject.h"
#include "configloader.h"

class taskMozilla : public TaskObject
{
    Q_OBJECT
public:
    explicit taskMozilla(QCheckBox* cb, QLabel* lab, QString path, QObject *parent);
    void run();

private:
    QString findRightPath(QDir *dir);
};

#endif // TASKMOZILLA_H
