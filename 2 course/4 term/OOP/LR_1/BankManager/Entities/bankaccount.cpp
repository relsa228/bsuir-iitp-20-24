#include "bankaccount.h"

const QString &BankAccount::getUserName() const
{
    return UserName;
}

void BankAccount::setUserName(const QString &newUserName)
{
    UserName = newUserName;
}

const QString &BankAccount::getBankName() const
{
    return BankName;
}

void BankAccount::setBankName(const QString &newBankName)
{
    BankName = newBankName;
}

int BankAccount::getAccId() const
{
    return AccId;
}

void BankAccount::setAccId(int newAccId)
{
    AccId = newAccId;
}

int BankAccount::getMoney() const
{
    return Money;
}

void BankAccount::setMoney(int newMoney)
{
    Money = newMoney;
}

const QString &BankAccount::getAccName() const
{
    return AccName;
}

void BankAccount::setAccName(const QString &newAccName)
{
    AccName = newAccName;
}

const QString &BankAccount::getType() const
{
    return Type;
}

void BankAccount::setType(const QString &newType)
{
    Type = newType;
}

BankAccount::BankAccount()
{

}
