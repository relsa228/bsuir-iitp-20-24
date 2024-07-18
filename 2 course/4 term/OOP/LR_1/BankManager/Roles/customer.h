#include "Entities/user.h"
#include "Entities/bankaccount.h"
#include "Entities/credit.h"

#ifndef CUSTOMER_H
#define CUSTOMER_H


class Customer: public User
{
public:
    QList<Credit*> *ListOfCredit;
    QList<BankAccount*> *ListOfAccounts; //список отурытых пользователем счетов

    Customer();
};

#endif // CUSTOMER_H
