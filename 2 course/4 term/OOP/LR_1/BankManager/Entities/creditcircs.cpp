#include "creditcircs.h"

const QString &CreditCircs::getBankName() const
{
    return BankName;
}

void CreditCircs::setBankName(const QString &newBankName)
{
    BankName = newBankName;
}

int CreditCircs::getTerms() const
{
    return Terms;
}

void CreditCircs::setTerms(int newTerms)
{
    Terms = newTerms;
}

int CreditCircs::getProc() const
{
    return Proc;
}

void CreditCircs::setProc(int newProc)
{
    Proc = newProc;
}

CreditCircs::CreditCircs()
{

}
