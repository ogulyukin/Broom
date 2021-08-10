#include "logger.h"
#include <QDateTime>
#include <QTextStream>

void Logger::execMessage(QString message)
{
    view->append(message);
    //statusbar->showMessage(message, 10000);
}

Logger::Logger(QTextBrowser *view, QStatusBar *statusbar) : view(view), statusbar(statusbar)
{

}

void Logger::addEvent(QString type, QString action, QString message)
{
    execMessage(QDateTime::currentDateTime().toString() + " " + type + " " + action + " " + message);
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
