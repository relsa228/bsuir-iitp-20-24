#ifndef ADMINISTRATORSERVICE_H
#define ADMINISTRATORSERVICE_H

#include "Srvices/managerservice.h"
#include "Srvices/databaseservice.h"
#include <QMessageBox>

class AdministratorService: public ManagerService
{
public:
    AdministratorService();
    void RejectCredit(int index, QString status);
    void RejectSalaryProject(int index, QString name);
    void Ban(int index, QString name);
};

#endif // ADMINISTRATORSERVICE_H
