#include "tableservice.h"

TableService::TableService(QTableWidget *newTable)
{
    table = newTable;

    table->setColumnCount(3);
    for (int i = 0; i < 3; i++)
        table->setColumnWidth(i, 260);

    table->setHorizontalHeaderLabels(QStringList()<< "Имя" << "Значение" << "Тип");
}

void TableService::AddUnitToTable(RegUnit unit)
{
    uint rows = table->rowCount();
    table->setRowCount(rows + 1);

    QTableWidgetItem *name = new QTableWidgetItem(QObject::tr("%1").arg(unit.getUnitName()));
    table->setItem(rows, 0, name);
    table->item(rows, 0)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable|Qt::ItemIsEnabled);

    QTableWidgetItem *value = new QTableWidgetItem(QObject::tr("%1").arg(unit.getUnitValue()));
    table->setItem(rows, 1, value);
    table->item(rows, 1)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable|Qt::ItemIsEnabled);

    QTableWidgetItem *type = new QTableWidgetItem(QObject::tr("%1").arg(unit.getUnitType()));
    table->setItem(rows, 2, type);
    table->item(rows, 2)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
}

void TableService::AddUnitsToTable(QVector<RegUnit> *units)
{
    for(auto unit: *units)
        AddUnitToTable(unit);
}
