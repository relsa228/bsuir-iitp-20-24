#ifndef WORK_H
#define WORK_H

#include <QString>
#include <QStringList>
#include <QList>

#include "Entities/author.h"
#include "Entities/genre.h"
#include "Entities/worktype.h"

class Work
{
public:
    Work(QString id, QString name, int edition_number, WorkType* type);
    Work();

    QList<Genre*>* genres;
    QList<Author*>* authors;
    const QString &getId() const;
    const QString &getName() const;
    int getEdition_number() const;
    WorkType *getType() const;

    void setId(const QString &newId);
    void setName(const QString &newName);
    void setEdition_number(int newEdition_number);
    void setType(WorkType *newType);

private:
    QString id;
    QString name;
    int edition_number;
    WorkType* type;
};

#endif // WORK_H
