#include "operatorservice.h"

OperatorService::OperatorService()
{

}

void OperatorService::ApproveSalaryProject(int index, QString operatorName)
{
    QString aproveStatus = "Aprove by operator", type = "operator";

    DataBaseService* db = new DataBaseService();
    db->AproveSalaryProject(index, aproveStatus, operatorName, type);
}

void OperatorService::CancelCustomerTransfer(Transfer* transfer, QString operName)
{
    Transfer* rejectTransfer = new Transfer();
    rejectTransfer->setInit(operName);
    rejectTransfer->setSenderId(transfer->getTargetId());
    rejectTransfer->setSum(transfer->getSum());
    rejectTransfer->setTargetId(transfer->getSenderId());
    rejectTransfer->setTransferId(transfer->getTransferId());
    rejectTransfer->setAprove("Cancle transfer");

    DataBaseService* db = new DataBaseService();
    db->TransferCash(rejectTransfer);
}
