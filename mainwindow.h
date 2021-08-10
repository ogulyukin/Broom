#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCheckBox>
#include <QLabel>
#include "logger.h"

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
