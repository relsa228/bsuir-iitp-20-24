#include "operator.h"
#include "enterprisespecialist.h"

#ifndef MANAGER_H
#define MANAGER_H


class Manager: public Operator
{
public:
    QList<Credit*>* creditList;
    QList<SalaryProject*>* salaryList;
    QList<Transfer*>* transferList;
    QList<User*>* userList;

    Manager();
};

#endif // MANAGER_H
