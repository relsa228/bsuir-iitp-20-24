#include "processservice.h"

ProcessService::ProcessService()
{

}

Process *ProcessService::createProcess(QString exeFile)
{
    QString rootDir = getProcessRootDir(exeFile);

    QProcess* process = new QProcess();
    process->setWorkingDirectory(rootDir);
    process->setProcessChannelMode(QProcess::MergedChannels);
    process->start(exeFile);

    Process* proc = new Process();
    proc->setProcessSign(process);
    proc->setProcName(getProcessName(exeFile));
    proc->setProcRootDir(rootDir);

    proc->setProcStatus(process->state());
    proc->setProcExitState(process->exitStatus());
    proc->setProcError(process->error());

    return proc;
}

void ProcessService::terminateProcess(Process *process)
{
    QProcess* runProc = process->getProcessSign();
    runProc->kill();

    process->setProcStatus(runProc->state());
    process->setProcExitState(runProc->exitStatus());
    process->setProcError(runProc->error());
}

void ProcessService::closeProcess(Process *process)
{
    QProcess* runProc = process->getProcessSign();
    runProc->close();

    process->setProcStatus(runProc->state());
    process->setProcExitState(runProc->exitStatus());
    process->setProcError(runProc->error());
}

void ProcessService::rerunProcess(Process *process)
{
    QProcess* runProc = process->getProcessSign();
    runProc->kill();

    QProcess* newProc = new QProcess();
    newProc->setWorkingDirectory(process->getProcRootDir());
    newProc->setProcessChannelMode(QProcess::MergedChannels);
    newProc->start(process->getProcRootDir() + process->getProcName() + ".exe");
    process->setProcessSign(newProc);

    process->setProcStatus(newProc->state());
    process->setProcExitState(newProc->exitStatus());
    process->setProcError(newProc->error());
}


////////////////////private processes///////////////////////////////////
QString ProcessService::getProcessRootDir(QString exePath)
{
    while(true){
        if (exePath.length() == 0)
            return "";
        if (exePath.last(1) != '/')
            exePath.chop(1);
        else
            return exePath;
    }
}

QString ProcessService::getProcessName(QString exePath)
{
    QString resultStr = "";

    while(true) {
        if (exePath.length() == 0)
            return "";
        if (exePath.last(1) != '/') {
            resultStr.push_front(exePath.last(1));
            exePath.chop(1);
        }
        else
            break;
    }

    while(true) {
        if (resultStr.length() == 0)
            return "";
        if (resultStr.last(1) != '.') {
            resultStr.chop(1);
        }
        else {
            resultStr.chop(1);
            return resultStr;
        }
    }
}
