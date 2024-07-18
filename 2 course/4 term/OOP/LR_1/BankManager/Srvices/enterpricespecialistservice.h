#ifndef ENTERPRICESPECIALISTSERVICE_H
#define ENTERPRICESPECIALISTSERVICE_H

#include "Srvices/databaseservice.h"

class EnterpriceSpecialistService
{
public:
    EnterpriceSpecialistService();
    void AproveSalaryProject(int salaryIndex, QString name);
    bool CorporateTransfer(int senderId, int targetId, int sum, QString initName);
};

#endif // ENTERPRICESPECIALISTSERVICE_H
