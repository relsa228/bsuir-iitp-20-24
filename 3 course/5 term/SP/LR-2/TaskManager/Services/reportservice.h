#ifndef REPORTSERVICE_H
#define REPORTSERVICE_H

#include <QString>
#include <QVector>

#include <Entities/process.h>

class ReportService
{
public:
    ReportService();
    QString getReport(QVector<Process*> procCollection, QString date);

private:
    QString getReportForProcess(Process* process);
};

#endif // REPORTSERVICE_H
