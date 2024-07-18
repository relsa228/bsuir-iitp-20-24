#ifndef GENRE_H
#define GENRE_H

#include <QString>

class Genre
{
public:
    Genre();
    Genre(int id, const QString &genre);

    int getId() const;
    void setId(int newId);

    const QString &getGenre() const;
    void setGenre(const QString &newGenre);

private:
    int id;
    QString genre;
};

#endif // GENRE_H
