#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCheckBox>
#include <QLabel>
#include "logger.h"
#include <QThread>
#include "ui_mainwindow.h"
#include "configloader.h"
#include "folderchecker.h"
#include "dirinfo.h"
#include <QDebug>
#include <QGridLayout>
#include <QMessageBox>
#include <QThreadPool>

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

private:
    Ui::MainWindow *ui;
    QMap<QString, QString> *configMap;
    QList<QCheckBox*> myCboxes;
    QList<QLabel*> myLabels;
    void checkAllCb();
    void unCheckAllCb();
};
#endif // MAINWINDOW_H
