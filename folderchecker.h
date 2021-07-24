#ifndef FOLDERCHECKER_H
#define FOLDERCHECKER_H
#include <QString>
#include <QCheckBox>
#include <QDir>
#include "dirinfo.h"
#include "logger.h"
class FolderChecker
{
    static int fileCountsCollector(QString path, int &dirC, int &sizeC, int &otherC);
    static void qListSum(QList<QFileInfo>* list, QList<QFileInfo> *other);
    //static void getIteratorPos(QList<QFileInfo>::iterator &it);
    static void collectTargets(QString path, QString ignore, Logger *log);
    static void printResult(QFileInfo &it, Logger *log);
public:
    static void isExistDir(QCheckBox* cb, QString path, DirInfo &DI);
    static void deleteFiles(QString path, Logger *log);
    //FolderChecker();
};

#endif // FOLDERCHECKER_H
