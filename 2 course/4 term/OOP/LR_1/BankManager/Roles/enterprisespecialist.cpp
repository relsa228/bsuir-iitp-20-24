#include "enterprisespecialist.h"

Company *EnterpriseSpecialist::getCompany() const
{
    return company;
}

void EnterpriseSpecialist::setCompany(Company *newCompany)
{
    company = newCompany;
}

EnterpriseSpecialist::EnterpriseSpecialist()
{

}
