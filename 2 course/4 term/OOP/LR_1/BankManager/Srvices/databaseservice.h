#ifndef DATABASESERVICE_H
#define DATABASESERVICE_H

#include <QtSql>
#include "Roles/customer.h"
#include "Entities/bank.h"
#include "Entities/credit.h"
#include "Entities/transfer.h"
#include "Entities/salaryproject.h"
#include "Entities/company.h"
#include "Entities/creditcircs.h"

class QSqlDatabase;

class DataBaseService
{
public:
    DataBaseService();

    QSqlDatabase OpenDataBase();
    void CreateShema(QSqlDatabase sdb);

    User* Login(QString email, QString password);

    void AddCustomer(Customer* customer, QString password);
    void SetCustomerStatus(int index, QString verdict, QString name);

    QList<BankAccount*>* GetBankAccounts (QString userName);
    QList<Bank*>* GetBanks ();
    QList<Credit*>* GetCredits(QString userName);
    QList<CreditCircs*>* GetCreditCircs();
    QStringList GetCompanyName();
    QList<SalaryProject*>* GetSalaryProjects (QString companyName);
    Company* GetCompany(QString companyName);
    QList<Transfer*>* GetTransfers (QString transferType);
    QList<User*>* GetUsers(QString type);

    void AddBankAccount(BankAccount* bankAccount, QString type);
    void CloseBankAccount(QString userName, int accId);

    bool AddCredit(Credit* credit);
    void CancleCredit(int index, QString status);
    bool AproveCredit(int creditName, Transfer* transfer);

    bool TransferCash(Transfer* transfer);
    void InOutOperation(Transfer* transfer, int operationIndex);
    bool CreateCorporativeTransfer(Transfer *transfer, QString aprove);

    void CreateSalaryProject(SalaryProject* salaryProject, QString bankName);
    void AproveSalaryProject(int salaryIndex, QString aproveStatus, QString name, QString type);
    void CancleSalaryProject(int index, QString name);

};

#endif // DATABASESERVICE_H
