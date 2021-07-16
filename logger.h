#ifndef LOGGER_H
#define LOGGER_H
#include <QTextBrowser>
#include <QFile>
#include <QDir>
#include <QString>
#include <QStatusBar>

class Logger
{
    QTextBrowser *view;
    QStatusBar *statusbar;
    void execMessage(QString message);
public:
    Logger(QTextBrowser *view, QStatusBar *statusbar);
    void addEvent(QString type, QString action, QString message);
};

#endif // LOGGER_H
