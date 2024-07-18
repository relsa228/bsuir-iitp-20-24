#include "reportservice.h"

ReportService::ReportService()
{

}

QString ReportService::getReport(QVector<Process *> procCollection, QString date)
{
    QString report = "TaskManager report at " + date;

    foreach (Process* proc, procCollection) {
        report += "\n-------------------------------------------";
        report += getReportForProcess(proc);
    }
    report += "\n-------------------------------------------";

    return report;
}

QString ReportService::getReportForProcess(Process *process)
{
    QString result = "";
    result += "\nProcess name: " + process->getProcName();
    result += "\nProcess root dir: " + process->getProcRootDir();
    result += "\nCurrent status: " + process->getProcStatus();
    result += "\nExit status: " + process->getProcExitState();
    result += "\nError status: " + process->getProcError();

    return result;
}
