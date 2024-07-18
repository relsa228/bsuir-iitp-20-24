#ifndef PRINTCENTER_H
#define PRINTCENTER_H

#include <QString>

class PrintCenter
{
public:
    PrintCenter();
    PrintCenter(const QString &id, const QString &adress, int batch_in_progress, int publication_batch);

    const QString &getId() const;
    void setId(const QString &newId);
    const QString &getAdress() const;
    void setAdress(const QString &newAdress);
    int getBatch_in_progress() const;
    void setBatch_in_progress(int newBatch_in_progress);
    int getPublication_batch() const;
    void setPublication_batch(int newPublication_batch);

private:
    QString id;
    QString adress;
    int batch_in_progress;
    int publication_batch;
};

#endif // PRINTCENTER_H
