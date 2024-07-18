#ifndef USER_H
#define USER_H

#include "QString"

class Action;

class User
{
private:
    int UserId;
    QString Name;
    QString Surname;
    QString PassportSeries;
    QString PassportNum;
    QString Telephone;
    QString CompanyName;
    QString Email;
    QString RoleId;
    QString AproveStatus;
public:
    User();
    virtual ~User();

    const QString &getName() const;
    void setName(const QString &newName);

    const QString &getPassportSeries() const;
    void setPassportSeries(const QString &newPassportSeries);

    const QString &getPassportNum() const;
    void setPassportNum(const QString &newPassportNum);

    const QString &getTelephone() const;
    void setTelephone(const QString &newTelephone);

    const QString &getEmail() const;
    void setEmail(const QString &newEmail);

    const QString &getSurname() const;
    void setSurname(const QString &newSurname);

    const QString &getRoleId() const;
    void setRoleId(const QString &newRoleId);

    const QString &getCompanyName() const;
    void setCompanyName(const QString &newCompanyName);
    int getUserId() const;
    void setUserId(int newUserId);
    const QString &getAproveStatus() const;
    void setAproveStatus(const QString &newAproveStatus);
};

#endif // USER_H
