#ifndef CREDITCIRCS_H
#define CREDITCIRCS_H

#include <QString>

class CreditCircs
{
private:
    QString BankName;
    int Terms;
    int Proc;
public:
    CreditCircs();
    const QString &getBankName() const;
    void setBankName(const QString &newBankName);
    int getTerms() const;
    void setTerms(int newTerms);
    int getProc() const;
    void setProc(int newProc);
};

#endif // CREDITCIRCS_H
