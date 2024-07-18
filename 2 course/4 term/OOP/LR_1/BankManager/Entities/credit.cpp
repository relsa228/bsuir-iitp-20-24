#include "credit.h"

const QString &Credit::getBankName() const
{
    return BankName;
}

void Credit::setBankName(const QString &newBankName)
{
    BankName = newBankName;
}

const QString &Credit::getUserName() const
{
    return UserName;
}

void Credit::setUserName(const QString &newUserName)
{
    UserName = newUserName;
}

int Credit::getSum() const
{
    return Sum;
}

void Credit::setSum(int newSum)
{
    Sum = newSum;
}

const QString &Credit::getAproveStatus() const
{
    return aproveStatus;
}

void Credit::setAproveStatus(const QString &newAproveStatus)
{
    aproveStatus = newAproveStatus;
}

int Credit::getAccIndex() const
{
    return AccIndex;
}

void Credit::setAccIndex(int newAccIndex)
{
    AccIndex = newAccIndex;
}

int Credit::getTerm() const
{
    return term;
}

void Credit::setTerm(int newTerm)
{
    term = newTerm;
}

int Credit::getProcent() const
{
    return procent;
}

void Credit::setProcent(int newProcent)
{
    procent = newProcent;
}

int Credit::getCreditId() const
{
    return creditId;
}

void Credit::setCreditId(int newCreditId)
{
    creditId = newCreditId;
}

Credit::Credit()
{

}
