#include <QString>

#ifndef SALARYPROJECT_H
#define SALARYPROJECT_H


class SalaryProject
{
private:
    int Index;
    QString ApproveStatus;
    int BIK;
    int PrevBIK;
    QString CompanyName;
    QString Username;
    QString Specialist;
    QString Operator;
public:
    SalaryProject();
    const QString &getApproveStatus() const;
    void setApproveStatus(const QString &newApproveStatus);
    int getBIK() const;
    void setBIK(int newBIK);
    const QString &getCompanyName() const;
    void setCompanyName(const QString &newCompanyName);
    const QString &getUsername() const;
    void setUsername(const QString &newUsername);
    int getIndex() const;
    void setIndex(int newIndex);
    const QString &getSpecialist() const;
    void setSpecialist(const QString &newSpecialist);
    const QString &getOperator() const;
    void setOperator(const QString &newOperator);
    int getPrevBIK() const;
    void setPrevBIK(int newPrevBIK);
};

#endif // SALARYPROJECT_H
