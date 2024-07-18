#include "Entities/user.h"
#include "Entities/credit.h"
#include "Entities/salaryproject.h"
#include "Entities/transfer.h"

#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H


class Administrator: public User
{
public:
    QList<Credit*>* creditList;
    QList<SalaryProject*>* salaryList;
    QList<Transfer*>* transferList;
    QList<User*>* userList;

    Administrator();
    ~Administrator();
};

#endif // ADMINISTRATOR_H
