#include "loggerservice.h"

LoggerService::LoggerService(QSqlDatabase database)
{
    this->database = database;
}

void LoggerService::writeLog(Log *log)
{
    QSqlQuery* query = new QSqlQuery(database);
    QString currentDate = QDateTime::currentDateTime().toString("yyyy.MM.dd HH:mm:ss").replace(".", "-");
    query->exec("INSERT INTO logs VALUES ('" + log->getDoerId() + "', '" + log->getAction() + "', '" + log->getObjectId() + "', '" + log->getObjectType() + "', '" + currentDate + "')");
}

QList<Log *> *LoggerService::getLogs()
{
    QList<Log *> *result = new QList<Log *>();
    QSqlQuery* query = new QSqlQuery(database);
    query->exec("SELECT * FROM logs");
    while(query->next())
        result->push_back(new Log(query->value(0).toString(), query->value(1).toString(), query->value(2).toString(), query->value(3).toString(), query->value(4).toString()));

    return result;
}
