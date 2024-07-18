#include "administratorservice.h"

AdministratorService::AdministratorService()
{

}

void AdministratorService::RejectCredit(int index, QString status)
{
    DataBaseService* db = new DataBaseService();
    db->CancleCredit(index, status);
}

void AdministratorService::RejectSalaryProject(int index, QString name)
{
    DataBaseService* db = new DataBaseService();
    db->CancleSalaryProject(index, name);
}

void AdministratorService::Ban(int index, QString name)
{
    DataBaseService* db = new DataBaseService();
    db->SetCustomerStatus(index, "ban", name);
}
