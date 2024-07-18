#include "author.h"

Author::Author(QString id, QString name, QString surname, QString patronymic, int work_count) {
    this->id = id;
    this->name = name;
    this->surname = surname;
    this->patronymic = patronymic;
    this->work_count = work_count;
}

Author::Author()
{

}

const QString &Author::getId() const
{
    return id;
}

const QString &Author::getName() const
{
    return name;
}

const QString &Author::getSurname() const
{
    return surname;
}

const QString &Author::getPatronymic() const
{
    return patronymic;
}

int Author::getWork_count() const
{
    return work_count;
}
