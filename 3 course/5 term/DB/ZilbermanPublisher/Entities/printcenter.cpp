#include "printcenter.h"

PrintCenter::PrintCenter()
{

}

PrintCenter::PrintCenter(const QString &id, const QString &adress, int batch_in_progress, int publication_batch) : id(id),
    adress(adress),
    batch_in_progress(batch_in_progress),
    publication_batch(publication_batch)
{}

const QString &PrintCenter::getId() const
{
    return id;
}

void PrintCenter::setId(const QString &newId)
{
    id = newId;
}

const QString &PrintCenter::getAdress() const
{
    return adress;
}

void PrintCenter::setAdress(const QString &newAdress)
{
    adress = newAdress;
}

int PrintCenter::getBatch_in_progress() const
{
    return batch_in_progress;
}

void PrintCenter::setBatch_in_progress(int newBatch_in_progress)
{
    batch_in_progress = newBatch_in_progress;
}

int PrintCenter::getPublication_batch() const
{
    return publication_batch;
}

void PrintCenter::setPublication_batch(int newPublication_batch)
{
    publication_batch = newPublication_batch;
}
