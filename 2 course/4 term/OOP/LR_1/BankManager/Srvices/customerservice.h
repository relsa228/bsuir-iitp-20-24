#ifndef CUSTOMERSERVICE_H
#define CUSTOMERSERVICE_H

#include "Entities/bankaccount.h"
#include "Roles/customer.h"
#include "Srvices/databaseservice.h"
#include "Entities/salaryproject.h"

class DataBaseService;

class CustomerService
{
public:
    CustomerService();
    void OpenBankAccount(Customer* customer, QString bankName, QString accName);
    void CloseBankAccount(QString userName, int accId);
    bool CheckoutCredit(Customer* customer, int accIndex, QString bankName, int sum, CreditCircs* creditCircs);
    bool TransferOperation(int sum, int targetId, int userId, QString initName);
    void CashInOut(int accId, int sum, int operationIndex);
    void CreateSalaryProject(QString username, QString bankName, QString companyName);
};

#endif // CUSTOMERSERVICE_H
