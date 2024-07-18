#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QString>

class Customer
{
public:
    Customer();
    Customer(QString id, QString name, QString spec, int order_count);

    const QString &getId() const;

    const QString &getSpec() const;

    const QString &getName() const;

    int getOrder_count() const;

private:
    QString id;
    QString spec;
    QString name;
    int order_count;
};

#endif // CUSTOMER_H
