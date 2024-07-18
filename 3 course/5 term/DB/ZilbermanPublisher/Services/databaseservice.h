#ifndef DATABASESERVICE_H
#define DATABASESERVICE_H

#include <QString>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QList>
#include <QUuid>

#include "Entities/genre.h"
#include "Entities/manager.h"
#include "Entities/customer.h"
#include "Entities/order.h"
#include "Entities/batch.h"
#include "Entities/author.h"
#include "Entities/work.h"
#include "Entities/printcenter.h"
#include "Entities/worktype.h"
#include "Entities/position.h"

#include "Services/loggerservice.h"

class DatabaseService
{
public:
    DatabaseService();

    Manager* getManager(QString login, QString password);
    QList<Customer*>* getCustomersViaManager(QString login);
    QList<Order*>* getOrders(QString login);
    QList<Author*>* getAuthors();
    QList<Work*>* getWorks();
    QList<PrintCenter*>* getPrintCenters();
    PrintCenter* getPrintCenterViaManager(Manager* manager);
    QList<WorkType*>* getWorkTypes();
    QList<Genre*>* getGenres();
    QList<Batch*>* getReadyBatches(QString printCenterId);
    QList<Batch*>* getOnWorkBatches(QString printCenterId);
    QList<Manager*>* getManagers();
    QList<Position*>* getPositions();
    QList<Log*>* getLogs();

    void addAuthor(QString name, QString surname, QString ptr, QString managerID);
    void addCustomer(QString name, QString spec, QString managerID);
    void createOrder(Order* order,  QString managerId);
    void addWork(Work* newWork, QString managerID);
    void addManager(Manager *newManager, QString password);

    void changeOrderStatus(QString orderId, QString managerId);
    void changeBatchPrintStatus(QString batchId, QString status, QString managerId);
    void changeManagerStatus(QString managerId, QString status);
    void changeManagerPassword(QString managerId, QString newPassword);
    void updateLastAuthTime(QString managerId);

private:
    QSqlDatabase database;
    LoggerService *logger;
};

#endif // DATABASESERVICE_H
