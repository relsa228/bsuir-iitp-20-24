#include "Entities/user.h"
#include "Entities/salaryproject.h"
#include "Entities/transfer.h"
#include "Entities/salaryproject.h"
#include "customer.h"

#ifndef OPERATOR_H
#define OPERATOR_H


class Operator: public User
{
public:
    QList<Transfer*> *userTransfers;
    QList<SalaryProject*> *salaryList;

    Operator();
};

#endif // OPERATOR_H
