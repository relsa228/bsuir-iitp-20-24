#include "genre.h"

Genre::Genre()
{

}

Genre::Genre(int id, const QString &genre) : id(id),
    genre(genre)
{}

int Genre::getId() const
{
    return id;
}

void Genre::setId(int newId)
{
    id = newId;
}

const QString &Genre::getGenre() const
{
    return genre;
}

void Genre::setGenre(const QString &newGenre)
{
    genre = newGenre;
}
