#include "reciclebintask.h"

RecicleBinTask::RecicleBinTask(QCheckBox* cb, QLabel* lab, QString path, QObject *parent) : TaskObject(cb, lab, path, parent)
{
    elements = 1;
}

void RecicleBinTask::run()
{
    SHEmptyRecycleBin(0,0,SHERB_NOCONFIRMATION | SHERB_NOPROGRESSUI | SHERB_NOSOUND);
    emit sendMsg("УСПЕХ","Удаление", QThread::currentThread()->objectName() + "Очистка Корзины");
    emit deleted();
    cb->setChecked(false);
}

