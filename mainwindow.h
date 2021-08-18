#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "logger.h"
#include "ui_mainwindow.h"
#include "configloader.h"
#include <QDebug>
#include <QGridLayout>
#include <QMessageBox>
#include <QThreadPool>
#include <QTimer>
#include "reciclebintask.h"
#include "userpathtask.h"
#include "taskthread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Logger *log;

signals:
    void sendMsg(QString type, QString actions, QString msg);

private slots:
    void on_pushButton_clicked();

    void on_cbAll_stateChanged(int arg1);

    void on_actionAbout_Qt_triggered();

    void on_actionAbout_triggered();

    void on_clearLogButton_clicked();

public slots:
    void deleteCounter();
    void finishProgressBar();

private:
    Ui::MainWindow *ui;
    QMap<QString, QString> *configMap;
    QList<TaskObject*> taskList;
    //QList<QCheckBox*> myCboxes;
    //QList<QLabel*> myLabels;
    //QMap<QString, int> foundElements;
    int AllElementsSelected;
    int _tic;
    QTimer timer;
    int deletedCount;
    void checkAllCb();
    void unCheckAllCb();
    void calculateAllElementsSelected();
};
#endif // MAINWINDOW_H
