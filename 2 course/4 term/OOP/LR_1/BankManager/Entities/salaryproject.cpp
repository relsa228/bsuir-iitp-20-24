#include "salaryproject.h"

const QString &SalaryProject::getApproveStatus() const
{
    return ApproveStatus;
}

void SalaryProject::setApproveStatus(const QString &newApproveStatus)
{
    ApproveStatus = newApproveStatus;
}

int SalaryProject::getBIK() const
{
    return BIK;
}

void SalaryProject::setBIK(int newBIK)
{
    BIK = newBIK;
}

const QString &SalaryProject::getCompanyName() const
{
    return CompanyName;
}

void SalaryProject::setCompanyName(const QString &newCompanyName)
{
    CompanyName = newCompanyName;
}

const QString &SalaryProject::getUsername() const
{
    return Username;
}

void SalaryProject::setUsername(const QString &newUsername)
{
    Username = newUsername;
}

int SalaryProject::getIndex() const
{
    return Index;
}

void SalaryProject::setIndex(int newIndex)
{
    Index = newIndex;
}

const QString &SalaryProject::getSpecialist() const
{
    return Specialist;
}

void SalaryProject::setSpecialist(const QString &newSpecialist)
{
    Specialist = newSpecialist;
}

const QString &SalaryProject::getOperator() const
{
    return Operator;
}

void SalaryProject::setOperator(const QString &newOperator)
{
    Operator = newOperator;
}

int SalaryProject::getPrevBIK() const
{
    return PrevBIK;
}

void SalaryProject::setPrevBIK(int newPrevBIK)
{
    PrevBIK = newPrevBIK;
}

SalaryProject::SalaryProject()
{

}
