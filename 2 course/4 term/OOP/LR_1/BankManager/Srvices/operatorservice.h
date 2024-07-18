#ifndef OPERATORSERVICE_H
#define OPERATORSERVICE_H

#include "Entities/salaryproject.h"
#include "Srvices/databaseservice.h"


class OperatorService
{
public:
    OperatorService();
    void ApproveSalaryProject(int index, QString operatorName);
    void CancelCustomerTransfer(Transfer* transfer, QString operName);
};

#endif // OPERATORSERVICE_H
