#ifndef COMPANY_H
#define COMPANY_H

#include <QString>

class Company
{
private:
    QString CompanyName;
    QString Type;
    int UNP;
    int BankBIK;
    QString Adress;
public:
    Company();
    const QString &getCompanyName() const;
    void setCompanyName(const QString &newCompanyName);
    const QString &getType() const;
    void setType(const QString &newType);
    int getUNP() const;
    void setUNP(int newUNP);
    int getBankBIK() const;
    void setBankBIK(int newBankBIK);
    const QString &getAdress() const;
    void setAdress(const QString &newAdress);
};

#endif // COMPANY_H
