#include "logger.h"
#include <QDateTime>
#include <QTextStream>

void Logger::execMessage(QString message)
{
    view->append(message);
    //statusbar->showMessage(message);
}

QString Logger::getTypeMessage(QString msg)
{
    if(msg == "УСПЕХ")
        msg = "<font color = \"green\"><b>УСПЕХ</b></font>";
    if(msg == "ОШИБКА")
        msg = "<font color = \"red\"><b>ОШИБКА</b></font>";
    if(msg == "ИНФО")
        msg = "<font color = \"yellow\"><b>ИНФО</b></font>";
    return msg;
}

Logger::Logger(QTextBrowser *view, QStatusBar *statusbar, QObject *parent) :  QObject(parent), view(view), statusbar(statusbar)
{
    filename = QDir::currentPath() + QDir::separator() + "log.txt";
}

void Logger::addMessage(QString type, QString action, QString message)
{

    execMessage(QDateTime::currentDateTime().toString() + " " + getTypeMessage(type) + " " + action + " " + message);
    QFile file("log.txt");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
          execMessage("<font color = \"red\"><b>ОШИБКА ОТКРЫТИЕ ФАЙЛА Невозможно открыть файл лога!!!</b></font>");
          return;
    }
    QTextStream ofstr(&file);
    ofstr << QDateTime::currentDateTime().toString() + " " + type + " " + action + " " + message + "\n";
    file.close();
}
