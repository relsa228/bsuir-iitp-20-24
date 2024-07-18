#ifndef MANAGERSERVICE_H
#define MANAGERSERVICE_H

#include "Srvices/operatorservice.h"

class ManagerService: public OperatorService
{
public:
    ManagerService();
    bool AproveCredit(Credit* credit, QString mangerName);
    void CancleCorpTransfer(int transferId);
    void AproveCustomer(int index, QString name);
};

#endif // MANAGERSERVICE_H
