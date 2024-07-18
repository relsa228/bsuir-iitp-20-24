#include "user.h"

const QString &User::getCompanyName() const
{
    return CompanyName;
}

void User::setCompanyName(const QString &newCompanyName)
{
    CompanyName = newCompanyName;
}

int User::getUserId() const
{
    return UserId;
}

void User::setUserId(int newUserId)
{
    UserId = newUserId;
}

const QString &User::getAproveStatus() const
{
    return AproveStatus;
}

void User::setAproveStatus(const QString &newAproveStatus)
{
    AproveStatus = newAproveStatus;
}

User::User(){}
User::~User(){}

const QString &User::getName() const
{
    return Name;
}

void User::setName(const QString &newName)
{
    Name = newName;
}

const QString &User::getPassportSeries() const
{
    return PassportSeries;
}

void User::setPassportSeries(const QString &newPassportSeries)
{
    PassportSeries = newPassportSeries;
}

const QString &User::getPassportNum() const
{
    return PassportNum;
}

void User::setPassportNum(const QString &newPassportNum)
{
    PassportNum = newPassportNum;
}

const QString &User::getTelephone() const
{
    return Telephone;
}

void User::setTelephone(const QString &newTelephone)
{
    Telephone = newTelephone;
}

const QString &User::getEmail() const
{
    return Email;
}

void User::setEmail(const QString &newEmail)
{
    Email = newEmail;
}

const QString &User::getSurname() const
{
    return Surname;
}

void User::setSurname(const QString &newSurname)
{
    Surname = newSurname;
}

const QString &User::getRoleId() const
{
    return RoleId;
}

void User::setRoleId(const QString &newRoleId)
{
    RoleId = newRoleId;
}
