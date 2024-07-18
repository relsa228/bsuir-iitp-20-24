#ifndef TRANSFER_H
#define TRANSFER_H

#include <QString>


class Transfer
{
private:
    int transferId;
    QString Init;
    int TargetId;
    int SenderId;
    int Sum;
    QString aprove;
public:
    Transfer();
    int getTargetId() const;
    void setTargetId(int newTargetId);
    int getSenderId() const;
    void setSenderId(int newUserId);
    int getSum() const;
    void setSum(int newSum);
    const QString &getInit() const;
    void setInit(const QString &newInit);
    int getTransferId() const;
    void setTransferId(int newTransferId);
    const QString &getAprove() const;
    void setAprove(const QString &newAprove);
};

#endif // TRANSFER_H
