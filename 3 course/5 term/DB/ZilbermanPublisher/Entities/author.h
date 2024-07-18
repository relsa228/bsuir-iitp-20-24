#ifndef AUTHOR_H
#define AUTHOR_H

#include <QString>

class Author
{
public:
    Author(QString id, QString name, QString surname, QString patronymic, int work_count);
    Author();

    const QString &getId() const;
    const QString &getName() const;
    const QString &getSurname() const;
    const QString &getPatronymic() const;
    int getWork_count() const;

private:
    QString id;
    QString name;
    QString surname;
    QString patronymic;
    int work_count;
};

#endif // AUTHOR_H
