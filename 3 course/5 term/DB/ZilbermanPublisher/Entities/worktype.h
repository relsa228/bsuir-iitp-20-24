#ifndef WORKTYPE_H
#define WORKTYPE_H

#include <QString>

class WorkType
{
public:
    WorkType();
    WorkType(int id, QString type);

    int getId() const;
    void setId(int newId);

    const QString &getType() const;
    void setType(const QString &newType);

private:
    int id;
    QString type;
};

#endif // WORKTYPE_H
