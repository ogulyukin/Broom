#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    configMap = ConfigLoader::readConfig("config.json");
    //qDebug() << "Всего считано полей: " << configMap->size();
    ui->setupUi(this);
    QMainWindow::setWindowTitle("Broom. Уборка мусора на вашем компе");
    log = new Logger(ui->textBrowser, ui->statusbar, this);
    connect(this, &MainWindow::sendMsg, log, &Logger::addMessage);
    connect(&timer, &QTimer::timeout, this, &MainWindow::finishProgressBar);
    emit sendMsg("ИНФО", "Запуск программы", "Считано " + QString::number(configMap->size()) + " записей кофигурационного файла");
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
        QString labStr = "Найдено " + QString::number(DI.filesC) + " файлов, " + QString::number(DI.dirC) + " папок, " + QString::number(DI.size/1024/1024) + " Мб";
        foundElements.insert(it.key(), DI.filesC + DI.dirC);
        myLabels.append(lab);
        if(!DI.dirC && !DI.filesC && !DI.size)
        {
            labStr = "Нечего удалять";
            cb->setDisabled(true);
        }
        if (it.value().contains("$RECYCLE.BIN"))
        {
            labStr = "Очистить корзину";
            cb->setEnabled(true);
        }
        lab->setText(labStr);
        cbLayout->addWidget(cb, count, 0);
        cbLayout->addWidget(lab, count, 1);
        count++;
    }
    ui->groupBox->setLayout(cbLayout);
    ui->tabWidget->setCurrentWidget(ui->tab);
    ui->progressBar->setValue(0);
}

MainWindow::~MainWindow()
{
    qDeleteAll(myCboxes);
    qDeleteAll(myLabels);
    //qDeleteAll(fcList);
    myCboxes.clear();
    myLabels.clear();
    //fcList.clear();
    delete log;
    delete ui;    
}


void MainWindow::on_pushButton_clicked()
{
    calculateAllElementsSelected();
    if(AllElementsSelected > 0)
    {
        QThreadPool *pool = QThreadPool::globalInstance();
        for (int i = 0; i < myCboxes.size(); i++)
        {
            if(myCboxes.at(i)->isChecked())
            {
                FolderChecker *fc = new FolderChecker(configMap->value(myCboxes.at(i)->text()), this);
                connect(fc, &FolderChecker::sendMsg, log, &Logger::addMessage);
                connect(fc, &FolderChecker::deleted, this, &MainWindow::deleteCounter);
                fc->setAutoDelete(true);
                pool->start(fc);
            }
        }
        pool->waitForDone();
        QMap<QString, QString>::iterator it;
        int count = 0;
        foundElements.clear();
        for(it = configMap->begin(); it != configMap->end(); it++)
        {
            DirInfo DI;
            FolderChecker::isExistDir(myCboxes.at(count), it.value(), DI);        
            if(!DI.dirC && !DI.filesC && !DI.size)
            {
                if (it.value().contains("$RECYCLE.BIN"))
                {
                    myLabels.at(count)->setText("Очистить корзину");
                    myCboxes.at(count)->setEnabled(true);
                }else
                {
                    myLabels.at(count)->setText("Нечего удалять");
                    myCboxes.at(count)->setDisabled(true);
                }
            }else
            {
                myLabels.at(count)->setText("Найдено " + QString::number(DI.filesC) + " файлов, " + QString::number(DI.dirC) + " папок, " + QString::number(DI.size/1024/1024) + " Мб");
                myCboxes.at(count)->setEnabled(true);
            }
            foundElements.insert(it.key(),DI.filesC + DI.dirC);
            count++;
        }
    }
    unCheckAllCb();
    ui->cbAll->setChecked(false);
    //AllElementsSelected = 0;
    //deletedCount = AllElementsSelected;
    timer.setInterval(2000);
    timer.start();
    //ui->progressBar->setValue(100);
    //QMessageBox::information(this, "Информация", "Задания по удалению завершены!");
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

void MainWindow::calculateAllElementsSelected()
{
     AllElementsSelected = 0;
     deletedCount = 0;
     ui->progressBar->setValue(0);
     _tic = 0;
    for (int i = 0; i < myCboxes.size(); i++)
    {
        if(myCboxes.at(i)->isChecked())
        {
            AllElementsSelected += foundElements.value(myCboxes.at(i)->text());
        }
    }
    emit sendMsg("ИНФО", "Подготовка", "Всего Элементов к удалению: " + QString::number(AllElementsSelected));
}

void MainWindow::on_cbAll_stateChanged(int arg1)
{
    Q_UNUSED(arg1);
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

void MainWindow::deleteCounter()
{
    deletedCount++;
    //qDebug() << "deletedCount = " + QString::number(deletedCount) + "AllElementSelected = " + QString::number(AllElementsSelected);
    if (AllElementsSelected == 0)
        return;
    //emit sendMsg("ИНФО", "ПРОВЕРКА", "deletedCount = " + QString::number(deletedCount) + "AllElementSelected = " + QString::number(AllElementsSelected));
    ui->progressBar->setValue(deletedCount * 100/(AllElementsSelected == 0 ? 1 : AllElementsSelected));
}

void MainWindow::finishProgressBar()
{
    ui->progressBar->setValue(100);
}

