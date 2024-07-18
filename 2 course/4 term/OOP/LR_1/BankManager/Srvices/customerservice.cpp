#include "customerservice.h"

CustomerService::CustomerService()
{

}

void CustomerService::OpenBankAccount(Customer* customer, QString bankName, QString accName)
{
    BankAccount* bankAccount = new BankAccount();
    bankAccount->setAccName(accName);
    bankAccount->setBankName(bankName);
    bankAccount->setUserName(customer->getEmail());
    bankAccount->setMoney(0);

    DataBaseService* db = new DataBaseService();
    db->AddBankAccount(bankAccount, "user");
}

void CustomerService::CloseBankAccount(QString userName, int accId)
{
    DataBaseService* db = new DataBaseService();
    db->CloseBankAccount(userName, accId);
}

bool CustomerService::CheckoutCredit(Customer* customer, int accIndex, QString bankName, int sum, CreditCircs* creditCircs)
{
    Credit* credit = new Credit();
    credit->setAccIndex(accIndex);
    credit->setAproveStatus("Waiting");
    credit->setBankName(bankName);
    credit->setSum(sum);
    credit->setUserName(customer->getEmail());
    credit->setTerm(creditCircs->getTerms());
    credit->setProcent(creditCircs->getProc());

    DataBaseService* db = new DataBaseService();
    return db->AddCredit(credit);
}

bool CustomerService::TransferOperation(int sum, int targetId, int userId, QString initName)
{
    Transfer* transfer = new Transfer();
    transfer->setSum(sum);
    transfer->setInit(initName);
    transfer->setTargetId(targetId);
    transfer->setSenderId(userId);
    transfer->setAprove("User transfer");

    DataBaseService* db = new DataBaseService();
    return db->TransferCash(transfer);
}

void CustomerService::CashInOut(int accId, int sum, int operationIndex)
{
    Transfer* transfer = new Transfer();
    transfer->setSum(sum);
    transfer->setSenderId(accId);

    DataBaseService* db = new DataBaseService();
    return db->InOutOperation(transfer, operationIndex);
}

void CustomerService::CreateSalaryProject(QString username, QString bankName, QString companyName)
{
    SalaryProject* salaryProject = new SalaryProject();
    salaryProject->setCompanyName(companyName);
    salaryProject->setUsername(username);
    salaryProject->setApproveStatus("Waiting for a documents");

    DataBaseService* db = new DataBaseService();
    db->CreateSalaryProject(salaryProject, bankName);
}
