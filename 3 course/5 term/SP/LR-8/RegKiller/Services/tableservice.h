#ifndef TABLESERVICE_H
#define TABLESERVICE_H

#include <QTableWidget>
#include <QVector>

#include "Entities/regunit.h"

class TableService
{
private:
    QTableWidget *table;

public:
    TableService(QTableWidget *newTable);
    void AddUnitToTable(RegUnit unit);
    void AddUnitsToTable(QVector<RegUnit> *units);
};

#endif // TABLESERVICE_H
