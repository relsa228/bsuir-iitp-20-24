#ifndef LOG_H
#define LOG_H

#include <qString>

class Log
{
public:
    Log();
    Log(const QString &doerId, const QString &action, const QString &objectId, const QString &objectType);
    Log(const QString &doerId, const QString &action, const QString &objectId, const QString &objectType, const QString &currentTime);

    const QString &getDoerId() const;
    const QString &getAction() const;
    const QString &getObjectId() const;
    const QString &getObjectType() const;
    const QString &getCurrentTime() const;

private:
    QString doerId;
    QString action;
    QString objectId;
    QString objectType;
    QString currentTime;
};

#endif // LOG_H
