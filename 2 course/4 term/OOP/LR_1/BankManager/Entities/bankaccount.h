#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <QString>

class BankAccount
{
private:
    QString AccName;
    QString UserName;
    QString BankName;
    QString Type;
    int AccId;
    int Money;
public:
    BankAccount();
    const QString &getUserName() const;
    void setUserName(const QString &newUserName);
    const QString &getBankName() const;
    void setBankName(const QString &newBankName);
    int getAccId() const;
    void setAccId(int newAccId);
    int getMoney() const;
    void setMoney(int newMoney);
    const QString &getAccName() const;
    void setAccName(const QString &newAccName);
    const QString &getType() const;
    void setType(const QString &newType);
};

#endif // BANKACCOUNT_H
