#ifndef CREDIT_H
#define CREDIT_H

#include <QString>


class Credit
{
private:
    QString BankName;
    QString UserName;
    int Sum;
    int AccIndex;
    int term;
    int procent;
    int creditId;
    QString aproveStatus;
public:
    Credit();
    const QString &getBankName() const;
    void setBankName(const QString &newBankName);
    const QString &getUserName() const;
    void setUserName(const QString &newUserName);
    int getSum() const;
    void setSum(int newSum);
    const QString &getAproveStatus() const;
    void setAproveStatus(const QString &newAproveStatus);
    int getAccIndex() const;
    void setAccIndex(int newAccIndex);
    int getTerm() const;
    void setTerm(int newTerm);
    int getProcent() const;
    void setProcent(int newProcent);
    int getCreditId() const;
    void setCreditId(int newCreditId);
};

#endif // CREDIT_H
