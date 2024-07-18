#include "bank.h"

const QString &Bank::getName() const
{
    return Name;
}

void Bank::setName(const QString &newName)
{
    Name = newName;
}

int Bank::getBudget() const
{
    return Budget;
}

void Bank::setBudget(int newBudget)
{
    Budget = newBudget;
}

int Bank::getBIK() const
{
    return BIK;
}

void Bank::setBIK(int newBIK)
{
    BIK = newBIK;
}

Bank::Bank()
{

}
