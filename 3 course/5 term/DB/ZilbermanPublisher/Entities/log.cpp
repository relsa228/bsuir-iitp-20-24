#include "log.h"

Log::Log()
{

}

Log::Log(const QString &doerId, const QString &action, const QString &objectId, const QString &objectType) : doerId(doerId),
    action(action),
    objectId(objectId),
    objectType(objectType)
{}

const QString &Log::getDoerId() const
{
    return doerId;
}

const QString &Log::getAction() const
{
    return action;
}

const QString &Log::getObjectId() const
{
    return objectId;
}

const QString &Log::getObjectType() const
{
    return objectType;
}

const QString &Log::getCurrentTime() const
{
    return currentTime;
}

Log::Log(const QString &doerId, const QString &action, const QString &objectId, const QString &objectType, const QString &currentTime) : doerId(doerId),
    action(action),
    objectId(objectId),
    objectType(objectType),
    currentTime(currentTime)
{}
