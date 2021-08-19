#ifndef TASK1C_H
#define TASK1C_H

#include "taskobject.h"
#include "configloader.h"

class task1C : public TaskObject
{
    Q_OBJECT
public:
    explicit task1C(QCheckBox* cb, QLabel* lab, QString path = "", QObject *parent = nullptr);
    void run();

private:
    QMap<QString, QString>* configMap;
    QList<QString> foundPath;
    void collectExistPath();
    void countTargets();
};

#endif // TASK1C_H
