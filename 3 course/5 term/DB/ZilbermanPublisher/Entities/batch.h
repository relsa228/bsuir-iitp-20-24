#ifndef BATCH_H
#define BATCH_H

#include <QString>

class Batch
{
public:
    Batch(QString orderID, QString work, QString print_center, QString print_state, int count_of_work);
    Batch(QString id, QString orderID, QString work, QString print_center, QString print_state, int count_of_work);

    const QString &getId() const;
    const QString &getOrder() const;
    const QString &getWork() const;
    const QString &getPrint_center() const;
    const QString &getPrint_state() const;
    int getCount_of_work() const;

private:
    QString id;
    QString order;
    QString work;
    QString print_center;
    QString print_state;
    int count_of_work;
};

#endif // BATCH_H
