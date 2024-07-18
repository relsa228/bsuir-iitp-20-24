#ifndef LOGGERSERVICE_H
#define LOGGERSERVICE_H

#include <QString>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QList>

#include <Entities/log.h>

class LoggerService
{
public:
    LoggerService(QSqlDatabase database);

    void writeLog(Log* log);
    QList<Log*>* getLogs();

private:
    QSqlDatabase database;
};

#endif // LOGGERSERVICE_H
