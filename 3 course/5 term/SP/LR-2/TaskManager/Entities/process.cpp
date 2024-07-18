#include "process.h"

const QString &Process::getProcName() const
{
    return procName;
}

void Process::setProcName(const QString &newProcName)
{
    procName = newProcName;
}

const QString &Process::getProcRootDir() const
{
    return procRootDir;
}

void Process::setProcRootDir(const QString &newProcRootDir)
{
    procRootDir = newProcRootDir;
}

QString Process::getProcStatus() const
{
    switch (procStatus) {
    case QProcess::NotRunning:
        return "Not running";
    case QProcess::Running:
        return "Running";
    case QProcess::Starting:
        return "Starting";
    }
}

void Process::setProcStatus(QProcess::ProcessState newProcStatus)
{
    procStatus = newProcStatus;
}

QProcess *Process::getProcessSign() const
{
    return processSign;
}

void Process::setProcessSign(QProcess *newProcessSign)
{
    processSign = newProcessSign;
}

QString Process::getProcExitState() const
{
    if(procStatus == QProcess::Running)
        return "-";

    switch (procExitState) {
    case QProcess::NormalExit:
        return "Normal exit";
    case QProcess::CrashExit:
        return "Crash";
    }
}

void Process::setProcExitState(const QProcess::ExitStatus &newProcExitState)
{
    procExitState = newProcExitState;
}

QString Process::getProcError() const
{
    if(procStatus == QProcess::Running || procExitState == QProcess::NormalExit)
        return "-";

    switch (procError) {
    case QProcess::FailedToStart:
        return "Normal exit";
    case QProcess::Crashed:
        return "Crash";
    case QProcess::Timedout:
        return "Normal exit";
    case QProcess::WriteError:
        return "Crash";
    case QProcess::ReadError:
        return "Normal exit";
    case QProcess::UnknownError:
        return "Crash";
    }
}

void Process::setProcError(const QProcess::ProcessError &newProcError)
{
    procError = newProcError;
}

Process::Process()
{

}
