#ifndef PROCESS_H
#define PROCESS_H

#include <QString>
#include <QProcess>

class Process
{
private:
    QString procName;
    QString procRootDir;
    QString procExeFile;

    QProcess::ProcessState procStatus;
    QProcess::ExitStatus procExitState;
    QProcess::ProcessError procError;

    QProcess* processSign;

public:
    Process();
    const QString &getProcName() const;
    void setProcName(const QString &newProcName);

    const QString &getProcRootDir() const;
    void setProcRootDir(const QString &newProcRootDir);

    QString getProcStatus() const;
    void setProcStatus(QProcess::ProcessState newProcStatus);

    QProcess *getProcessSign() const;
    void setProcessSign(QProcess *newProcessSign);

    QString getProcExitState() const;
    void setProcExitState(const QProcess::ExitStatus &newProcExitState);

    QString getProcError() const;
    void setProcError(const QProcess::ProcessError &newProcError);
};

#endif // PROCESS_H
