#include "managerservice.h"

ManagerService::ManagerService()
{

}

void ManagerService::CancleCorpTransfer(int transferId)
{
    Transfer* transfer = new Transfer();
    transfer->setTransferId(transferId);
    transfer->setAprove("Corporate reject");

    DataBaseService* db = new DataBaseService();
    db->TransferCash(transfer);
}

bool ManagerService::AproveCredit(Credit *credit, QString mangerName)
{
    Transfer* transfer = new Transfer();
    transfer->setInit(credit->getBankName());
    transfer->setAprove(mangerName);
    transfer->setSum(credit->getSum());
    transfer->setTargetId(credit->getAccIndex());

    DataBaseService* db = new DataBaseService();
    return db->AproveCredit(credit->getCreditId(), transfer);
}

void ManagerService::AproveCustomer(int index, QString name)
{
    DataBaseService* db = new DataBaseService();
    db->SetCustomerStatus(index, "aprove", name);
}
