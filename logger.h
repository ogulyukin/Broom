#ifndef LOGGER_H
#define LOGGER_H
#include <QTextBrowser>
#include <QFile>
#include <QDir>
#include <QString>
#include <QStatusBar>
#include <QSet>

class Logger: public QObject
{
    Q_OBJECT
    QTextBrowser *view;
    QStatusBar *statusbar;
    void execMessage(QString message);
    QString getTypeMessage(QString mesg);
    QString filename;

public:
    Logger(QTextBrowser *view, QStatusBar *statusbar, QObject *parent = nullptr);

public slots:
    void addMessage(QString type, QString action, QString message);
};


#endif // LOGGER_H
