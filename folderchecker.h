#ifndef FOLDERCHECKER_H
#define FOLDERCHECKER_H

#include <QString>
#include <QCheckBox>
#include <QDir>
#include <QThread>
#include <QRunnable>
#include <windows.h>
#include <shellapi.h>
#include "dirinfo.h"
#include "logger.h"

class FolderChecker : public QObject, public QRunnable
{
    Q_OBJECT
    static int fileCountsCollector(QString path, int &dirC, int &sizeC);
    void deleteTargets(QString path, QString ignore);
    void printResult(QFileInfo &it);
    QString path;

public:
    explicit FolderChecker(QString path, QObject *parent = nullptr);
    static void isExistDir(QCheckBox* cb, QString path, DirInfo &DI);
    void deleteFiles(QString path);
    void run();

signals:
    void sendMsg(QString type, QString actions, QString msg);

public slots:

};

#endif // FOLDERCHECKER_H
