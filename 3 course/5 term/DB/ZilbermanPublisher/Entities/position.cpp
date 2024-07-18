#include "position.h"

Position::Position()
{

}

Position::Position(int id, const QString &position) : id(id),
    position(position)
{}

const QString &Position::getPosition() const
{
    return position;
}

int Position::getId() const
{
    return id;
}
