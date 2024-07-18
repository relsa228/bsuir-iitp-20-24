#include "tableservice.h"

TableService::TableService(QTableWidget *initTable)
{
    table = initTable;

    table->setColumnCount(5);
    for (int i = 0; i < 5; i++)
        table->setColumnWidth(i, 148);
    table->setHorizontalHeaderLabels(QStringList()<< "Название процесса" << "Рабочая директория" << "Статус процесса" << "Статус выхода" << "Ошибки");
}

void TableService::pushNewProcess(Process* process)
{
    table->setRowCount(table->rowCount() + 1);

    QTableWidgetItem *procName = new QTableWidgetItem(QObject::tr("%1").arg(process->getProcName()));
    table->setItem(table->rowCount() - 1, 0, procName);
    table->item(table->rowCount() - 1, 0)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable|Qt::ItemIsEnabled);

    QTableWidgetItem *procRootDir = new QTableWidgetItem(QObject::tr("%1").arg(process->getProcRootDir()));
    table->setItem(table->rowCount() - 1, 1, procRootDir);
    table->item(table->rowCount() - 1, 1)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable|Qt::ItemIsEnabled);

    QTableWidgetItem *procStatus = new QTableWidgetItem(QObject::tr("%1").arg(process->getProcStatus()));
    table->setItem(table->rowCount() - 1, 2, procStatus);
    table->item(table->rowCount() - 1, 2)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable|Qt::ItemIsEnabled);

    QTableWidgetItem *exitStatus = new QTableWidgetItem(QObject::tr("%1").arg(process->getProcExitState()));
    table->setItem(table->rowCount() - 1, 3, exitStatus);
    table->item(table->rowCount() - 1, 3)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable|Qt::ItemIsEnabled);

    QTableWidgetItem *errors = new QTableWidgetItem(QObject::tr("%1").arg(process->getProcError()));
    table->setItem(table->rowCount() - 1, 4, errors);
    table->item(table->rowCount() - 1, 4)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable|Qt::ItemIsEnabled);

    processCollection.push_back(process);
}

void TableService::updateProcess(int row, Process* process)
{
    QTableWidgetItem *procName = new QTableWidgetItem(QObject::tr("%1").arg(process->getProcName()));
    table->setItem(row, 0, procName);
    table->item(row, 0)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable|Qt::ItemIsEnabled);

    QTableWidgetItem *procRootDir = new QTableWidgetItem(QObject::tr("%1").arg(process->getProcRootDir()));
    table->setItem(row, 1, procRootDir);
    table->item(row, 1)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable|Qt::ItemIsEnabled);

    QTableWidgetItem *procStatus = new QTableWidgetItem(QObject::tr("%1").arg(process->getProcStatus()));
    table->setItem(row, 2, procStatus);
    table->item(row, 2)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable|Qt::ItemIsEnabled);

    QTableWidgetItem *exitStatus = new QTableWidgetItem(QObject::tr("%1").arg(process->getProcExitState()));
    table->setItem(row, 3, exitStatus);
    table->item(row, 3)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable|Qt::ItemIsEnabled);

    QTableWidgetItem *errors = new QTableWidgetItem(QObject::tr("%1").arg(process->getProcError()));
    table->setItem(row, 4, errors);
    table->item(row, 4)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable|Qt::ItemIsEnabled);

    processCollection.replace(row, process);
}

void TableService::updateFullTable()
{
    int index = 0;
    foreach(Process* it, processCollection){
        it->setProcError(it->getProcessSign()->error());
        it->setProcExitState(it->getProcessSign()->exitStatus());
        it->setProcStatus(it->getProcessSign()->state());

        updateProcess(index, it);
        index++;
    }
}

void TableService::dropTable()
{
    table->clear();
    table->setHorizontalHeaderLabels(QStringList()<< "Название процесса" << "Рабочая директория" << "Статус процесса" << "Статус выхода" << "Ошибки");
    table->setRowCount(0);

    foreach (Process* it, processCollection)
        it->getProcessSign()->kill();
    processCollection.clear();
}
