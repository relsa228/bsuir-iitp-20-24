#include "customer.h"

Customer::Customer()
{

}

Customer::Customer(QString id, QString spec, QString name, int order_count)
{
    this->id = id;
    this->spec = spec;
    this->name = name;
    this->order_count = order_count;
}

const QString &Customer::getId() const
{
    return id;
}

const QString &Customer::getSpec() const
{
    return spec;
}

const QString &Customer::getName() const
{
    return name;
}

int Customer::getOrder_count() const
{
    return order_count;
}
