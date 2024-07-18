#ifndef TABLESERVICE_H
#define TABLESERVICE_H

#include <QTableWidget>

#include <Entities/process.h>
#include <QVector>

class TableService
{
public:
    QVector<Process*> processCollection;

private:
    QTableWidget *table;

public:
    TableService(QTableWidget *initTable);
    void pushNewProcess(Process* process);
    void updateProcess(int row, Process* process);
    void updateFullTable();
    void dropTable();
};

#endif // TABLESERVICE_H
