#include "Entities/user.h"
#include "Entities/salaryproject.h"
#include "Entities/company.h"

#ifndef ENTERPRISESPECIALIST_H
#define ENTERPRISESPECIALIST_H


class EnterpriseSpecialist: public User
{
private:
    Company* company;
public:
    QList<SalaryProject*>* salaryList;

    EnterpriseSpecialist();
    Company *getCompany() const;
    void setCompany(Company *newCompany);
};

#endif // ENTERPRISESPECIALIST_H
