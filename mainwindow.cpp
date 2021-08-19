#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    configMap = ConfigLoader::readConfig("config.json");
    ui->setupUi(this);
    QMainWindow::setWindowTitle("Broom. Уборка мусора на вашем компе");
    log = new Logger(ui->textBrowser, this);
    connect(this, &MainWindow::sendMsg, log, &Logger::addMessage);
    connect(&timer, &QTimer::timeout, this, &MainWindow::finishProgressBar);
    emit sendMsg("ИНФО", "Запуск программы", "Считано " + QString::number(configMap->size()) + " записей кофигурационного файла");
    QGridLayout *cbLayout = new QGridLayout(this);
    cbLayout->addWidget(ui->cbAll);
    int count = 1;

    //Recicle Bin
    QCheckBox *rcb = new QCheckBox("Очистка корзины", ui->groupBox);
    QLabel *rlab = new QLabel(this);
    TaskObject* rtask = new TaskTrashBox(rcb, rlab, "", this);
    taskList.append(rtask);
    connecter(rtask);
    cbLayout->addWidget(rcb, count, 0);
    cbLayout->addWidget(rlab, count, 1);
    count++;

    //1C
    QCheckBox *ccb = new QCheckBox("Кэш 1С", ui->groupBox);
    QLabel *clab = new QLabel(this);
    TaskObject* ctask = new task1C(ccb, clab, "", this);
    taskList.append(ctask);
    connecter(ctask);
    cbLayout->addWidget(ccb, count, 0);
    cbLayout->addWidget(clab, count, 1);
    count++;

    //UserPath
    for(auto it = configMap->begin(); it != configMap->end(); it++)
    {
        QCheckBox *cb = new QCheckBox(it.key(),ui->groupBox);
        QLabel *lab = new QLabel(this);
        TaskObject* task = new TaskUserPAth(cb, lab, it.value(), this);
        connecter(task);
        taskList.append(task);
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
    delete log;
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    calculateAllElementsSelected();
    if(AllElementsSelected > 0)
    {
        QThreadPool *pool = QThreadPool::globalInstance();
        foreach(auto i, taskList)
        {
            if(i->isCheckboxChecked())
            {
                TaskThread *tt = new TaskThread(i);
                tt->setAutoDelete(true);
                pool->start(tt);
            }
        }
        pool->waitForDone();
    }
    ui->cbAll->setChecked(false);
    timer.setInterval(2000);
    timer.start();
    //QMessageBox::information(this, "Информация", "Задания по удалению завершены!");
}

void MainWindow::checkAllCb()
{
    foreach(auto i, taskList)
    {
        if(i->isCheckboxEnabled())
            i->setCheckBoxChecked();
    }
}

void MainWindow::unCheckAllCb()
{
    foreach(auto i, taskList)
    {
        if(i->isCheckboxEnabled())
            i->setCheckBoxUnchecked();
    }
}

void MainWindow::calculateAllElementsSelected()
{
    AllElementsSelected = 0;
    deletedCount = 0;
    ui->progressBar->setValue(0);
    _tic = 0;
    foreach(auto i, taskList)
    {
        if(i->isCheckboxChecked())
            AllElementsSelected += i->getElements();
    }
    emit sendMsg("ИНФО", "Подготовка", "Всего Элементов к удалению: " + QString::number(AllElementsSelected));
}

void MainWindow::connecter(TaskObject* tobj)
{
    connect(tobj, &TaskObject::sendMsg, log, &Logger::addMessage, Qt::QueuedConnection);
    connect(tobj, &TaskObject::deleted, this, &MainWindow::deleteCounter, Qt::QueuedConnection);
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
    ui->progressBar->setValue(deletedCount * 100/(AllElementsSelected == 0 ? 1 : AllElementsSelected));
}

void MainWindow::finishProgressBar()
{
    ui->progressBar->setValue(100);
}

