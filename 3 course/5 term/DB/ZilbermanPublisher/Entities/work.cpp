#include "work.h"

Work::Work(QString id, QString name, int edition_number, WorkType* type)
{
    this->id = id;
    this->name = name;
    this->edition_number = edition_number;
    this->type = type;

    this->genres = new QList<Genre*>();
    this->authors = new QList<Author*>();
}

Work::Work()
{
    this->genres = new QList<Genre*>();
    this->authors = new QList<Author*>();
}

const QString &Work::getId() const
{
    return id;
}

const QString &Work::getName() const
{
    return name;
}

int Work::getEdition_number() const
{
    return edition_number;
}

WorkType *Work::getType() const
{
    return type;
}

void Work::setId(const QString &newId)
{
    id = newId;
}

void Work::setName(const QString &newName)
{
    name = newName;
}

void Work::setEdition_number(int newEdition_number)
{
    edition_number = newEdition_number;
}

void Work::setType(WorkType *newType)
{
    type = newType;
}
