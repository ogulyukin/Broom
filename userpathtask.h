#ifndef USERPATHTASK_H
#define USERPATHTASK_H

#include "taskobject.h"
#include <QThread>
#include <QDir>
#include "dirinfo.h"
#include <QDebug>

class UserPAthTask : public TaskObject
{
    Q_OBJECT
public:
    explicit UserPAthTask(QCheckBox* cb, QLabel* lab, QString path = "", QObject *parent = nullptr);
    void run();

private:
    int fileCountsCollector(QString path, int &dirC, int &sizeC);
    void deleteTargets(QString path, QString ignore);
    void printResult(QFileInfo &it);
    bool isExistDir();
};

#endif // USERPATHTASK_H
