#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "configloader.h"
#include "folderchecker.h"
#include "dirinfo.h"
#include <QDebug>
#include <QGridLayout>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    configMap = ConfigLoader::readConfig("config.json");
    //qDebug() << "Всего считано полей: " << configMap->size();
    ui->setupUi(this);
    log = new Logger(ui->textBrowser, ui->statusbar);
    log->addEvent("ИНФО", "Запуск программы", "Считано " + QString::number(configMap->size()) + " записей кофигурационного файла");
    QMap<QString, QString>::iterator it;
    QGridLayout *cbLayout = new QGridLayout(this);
    cbLayout->addWidget(ui->cbAll);
    int count = 1;
    for(it = configMap->begin(); it != configMap->end(); it++)
    {
        QCheckBox *cb = new QCheckBox(it.key(),ui->groupBox);
        myCboxes.append(cb);
        DirInfo DI;
        FolderChecker::isExistDir(cb, it.value(), DI);
        QLabel *lab = new QLabel(this);
        QString labStr = "Найдено " + QString::number(DI.filesC) + " файлов, " + QString::number(DI.dirC) + " папок, " + QString::number(DI.size) + " байт";
        myLabels.append(lab);
        if(!DI.dirC && !DI.filesC && !DI.size)
        {
            labStr = "Нечего удалять";
        }
        lab->setText(labStr);
        cbLayout->addWidget(cb, count, 0);
        cbLayout->addWidget(lab, count, 1);
        count++;
    }
    ui->groupBox->setLayout(cbLayout);
    ui->tabWidget->setCurrentWidget(ui->tab);
}

MainWindow::~MainWindow()
{
    for (int i = 0; i < myCboxes.size(); i++)
    {
        delete myCboxes.at(i);
        delete myLabels.at(i);
    }
    delete log;
    delete ui;    
}


void MainWindow::on_pushButton_clicked()
{
    ui->tabWidget->setCurrentWidget(ui->tab_2);
    for (int i = 0; i < myCboxes.size(); i++)
    {
        if(myCboxes.at(i)->isChecked())
        {
            //qDebug() << "Begin deleting " << configMap->value(myCboxes.at(i)->text());
            FolderChecker::deleteFiles(configMap->value(myCboxes.at(i)->text()), log);
        }
    }
     QMap<QString, QString>::iterator it;
     int count = 0;
     for(it = configMap->begin(); it != configMap->end(); it++)
     {
         DirInfo DI;
         FolderChecker::isExistDir(myCboxes.at(count), it.value(), DI);
         myLabels.at(count)->setText("Найдено " + QString::number(DI.filesC) + " файлов, " + QString::number(DI.dirC) + " папок, " + QString::number(DI.size) + " байт");
         count++;
     }
     ui->tabWidget->setCurrentWidget(ui->tab);
}
void MainWindow::createConfig()
{
    QMap<QString, QString> map;
    map.insert("Временные файлы пользователя", "%TEMP%");
    map.insert("Временные файлы Windows", "%systemroot%\\Temp");
    map.insert("Кэш Opera", "%homepath%\\AppData\\Local\\Opera Software\\Opera Stable\\Cache");
    map.insert("Кэш Gogle Chrome", "%homepath%\\AppData\\Local\\Google\\Chrome\\User Data\\Default\\Cache");
    map.insert("Кэш Яндекса", "%homepath%\\AppData\\Local\\Yandex\\YandexBrowser\\User Data\\Default\\Cache");
    map.insert("Кэш Mozilla Firefox", "%homepath%\\AppData\\Local\\Mozilla\\Firefox\\Profiles\\PROF.default\\cache2\\entries");
    map.insert("Кэш Microsoft Edge", "%homepath%\\AppData\\Local\\Microsoft\Edge\\User Data\\Default\\Cache");
    map.insert("Очистить корзину", "C:\\$RECYCLE.BIN");
    //ConfigLoader::writeConfig(map, "config.json");
}

void MainWindow::checkAllCb()
{
    for (int i = 0; i < myCboxes.size(); i++)
    {
        if(myCboxes.at(i)->isEnabled())
            myCboxes.at(i)->setChecked(true);
    }
}

void MainWindow::unCheckAllCb()
{
    for (int i = 0; i < myCboxes.size(); i++)
    {
        if(myCboxes.at(i)->isEnabled())
            myCboxes.at(i)->setChecked(false);
    }
}


void MainWindow::on_cbAll_stateChanged(int arg1)
{
    if(ui->cbAll->isChecked())
    {
        checkAllCb();
    }else
    {
        unCheckAllCb();
    }
}



void MainWindow::on_actionAbout_Qt_triggered()
{
    QApplication::aboutQt();
}


void MainWindow::on_actionAbout_triggered()
{
   QMessageBox::information(this, "О программе", "2021 г. О. Гулюкин\nПрограмма очищает мусор на вашем компьютере");
}


void MainWindow::on_clearLogButton_clicked()
{
    ui->textBrowser->clear();
}

