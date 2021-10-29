#ifndef DIRINFO_H
#define DIRINFO_H

#include <QObject>

class DirInfo
{
public:
    qint64 size;
    int items;
    int filesC;
    int dirC;
    DirInfo();
};

#endif // DIRINFO_H
