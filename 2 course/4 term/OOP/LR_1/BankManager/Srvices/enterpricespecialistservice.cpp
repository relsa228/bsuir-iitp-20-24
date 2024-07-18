#include "enterpricespecialistservice.h"

EnterpriceSpecialistService::EnterpriceSpecialistService()
{

}

void EnterpriceSpecialistService::AproveSalaryProject(int salaryIndex, QString name)
{
    QString aproveStatus = "Aprove by enterprice specialist", type = "specialist";

    DataBaseService* db = new DataBaseService();
    db->AproveSalaryProject(salaryIndex, aproveStatus, name, type);
}

bool EnterpriceSpecialistService::CorporateTransfer(int senderId, int targetId, int sum, QString initName)
{
    Transfer* transfer = new Transfer();
    transfer->setInit(initName);
    transfer->setSum(sum);
    transfer->setTargetId(targetId);
    transfer->setSenderId(senderId);

    DataBaseService* db = new DataBaseService();
    return db->CreateCorporativeTransfer(transfer, "Waiting");
}
