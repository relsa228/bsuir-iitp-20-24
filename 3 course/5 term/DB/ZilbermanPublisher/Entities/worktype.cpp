#include "worktype.h"

WorkType::WorkType()
{

}

WorkType::WorkType(int id, QString genre) : id(id),
    type(genre)
{}

int WorkType::getId() const
{
    return id;
}

void WorkType::setId(int newId)
{
    id = newId;
}

const QString &WorkType::getType() const
{
    return type;
}

void WorkType::setType(const QString &newType)
{
    type = newType;
}
