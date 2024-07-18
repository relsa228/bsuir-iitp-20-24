#include "company.h"

const QString &Company::getCompanyName() const
{
    return CompanyName;
}

void Company::setCompanyName(const QString &newCompanyName)
{
    CompanyName = newCompanyName;
}

const QString &Company::getType() const
{
    return Type;
}

void Company::setType(const QString &newType)
{
    Type = newType;
}

int Company::getUNP() const
{
    return UNP;
}

void Company::setUNP(int newUNP)
{
    UNP = newUNP;
}

int Company::getBankBIK() const
{
    return BankBIK;
}

void Company::setBankBIK(int newBankBIK)
{
    BankBIK = newBankBIK;
}

const QString &Company::getAdress() const
{
    return Adress;
}

void Company::setAdress(const QString &newAdress)
{
    Adress = newAdress;
}

Company::Company()
{

}
