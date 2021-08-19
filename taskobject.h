#ifndef TASKOBJECT_H
#define TASKOBJECT_H

#include <QObject>
#include <QCheckBox>
#include <QLabel>
#include <QDir>
#include <QDebug>
#include <QThread>
#include "dirinfo.h"

class TaskObject : public QObject
{
    Q_OBJECT
public:
    explicit TaskObject(QCheckBox* cb, QLabel* lab, QString path = "", QObject *parent = nullptr);
    virtual void run() = 0;
    bool isCheckboxChecked();
    bool isCheckboxEnabled();
    void setCheckBoxChecked();
    void setCheckBoxUnchecked();
    void seLabelText(QString text);
    int getElements();

signals:
    void sendMsg(QString type, QString actions, QString msg);
    void deleted();

protected:
    QCheckBox* cb;
    QLabel* lab;
    int elements;
    QString path;
    void emitResult(QFileInfo &it);
    void dirInfoCollector(QString path, int &fileC, int &dirC, int &sizeC);
    void clearDirectory(QString path, QString ignore);
    void removeDirectory(QString path);
};

#endif // TASKOBJECT_H
