#ifndef TASKOBJECT_H
#define TASKOBJECT_H

#include <QObject>
#include <QRunnable>
#include <QCheckBox>
#include <QLabel>

class TaskObject : public QObject, public QRunnable
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
};

#endif // TASKOBJECT_H
