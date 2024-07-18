#ifndef BANK_H
#define BANK_H

#include <QString>


class Bank
{
private:
    QString Name;
    int BIK;
    int Budget;
public:
    Bank();
    const QString &getName() const;
    void setName(const QString &newName);
    int getBudget() const;
    void setBudget(int newBudget);
    int getBIK() const;
    void setBIK(int newBIK);
};

#endif // BANK_H
