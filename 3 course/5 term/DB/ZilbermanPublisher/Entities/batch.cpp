#include "batch.h"

Batch::Batch(QString orderID, QString work, QString print_center, QString print_state, int count_of_work)
{
    this->order = orderID;
    this->work = work;
    this->count_of_work = count_of_work;
    this->print_state = print_state;
    this->print_center = print_center;
}

Batch::Batch(QString id, QString orderID, QString work, QString print_center, QString print_state, int count_of_work)
{
    this->id = id;
    this->order = orderID;
    this->work = work;
    this->count_of_work = count_of_work;
    this->print_state = print_state;
    this->print_center = print_center;
}

const QString &Batch::getId() const
{
    return id;
}

const QString &Batch::getOrder() const
{
    return order;
}

const QString &Batch::getWork() const
{
    return work;
}

const QString &Batch::getPrint_center() const
{
    return print_center;
}

const QString &Batch::getPrint_state() const
{
    return print_state;
}

int Batch::getCount_of_work() const
{
    return count_of_work;
}
