#include "transfer.h"

int Transfer::getTargetId() const
{
    return TargetId;
}

void Transfer::setTargetId(int newTargetId)
{
    TargetId = newTargetId;
}

int Transfer::getSenderId() const
{
    return SenderId;
}

void Transfer::setSenderId(int newUserId)
{
    SenderId = newUserId;
}

int Transfer::getSum() const
{
    return Sum;
}

void Transfer::setSum(int newSum)
{
    Sum = newSum;
}

const QString &Transfer::getInit() const
{
    return Init;
}

void Transfer::setInit(const QString &newInit)
{
    Init = newInit;
}

int Transfer::getTransferId() const
{
    return transferId;
}

void Transfer::setTransferId(int newTransferId)
{
    transferId = newTransferId;
}

const QString &Transfer::getAprove() const
{
    return aprove;
}

void Transfer::setAprove(const QString &newAprove)
{
    aprove = newAprove;
}

Transfer::Transfer()
{

}
