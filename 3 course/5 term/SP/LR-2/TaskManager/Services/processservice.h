#ifndef PROCESSSERVICE_H
#define PROCESSSERVICE_H

#include <QString>
#include <QProcess>

#include <Entities/process.h>
#include <Entities/ProcStatusEnum.h>

class ProcessService
{
public:
    ProcessService();

    Process* createProcess(QString exeFile);
    void terminateProcess(Process* process);
    void closeProcess(Process* process);
    void rerunProcess(Process* process);

private:
    QString getProcessRootDir(QString exePath);
    QString getProcessName(QString exePath);
};

#endif // PROCESSSERVICE_H
