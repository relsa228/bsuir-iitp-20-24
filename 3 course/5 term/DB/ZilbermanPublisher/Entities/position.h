#ifndef POSITION_H
#define POSITION_H

#include <QString>

class Position
{
public:
    Position();
    Position(int id, const QString &position);

    const QString &getPosition() const;

    int getId() const;

private:
    int id;
    QString position;
};

#endif // POSITION_H
