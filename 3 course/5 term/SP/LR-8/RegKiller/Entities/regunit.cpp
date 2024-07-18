#include "regunit.h"

const QString &RegUnit::getUnitValue() const
{
    return UnitValue;
}

void RegUnit::setUnitValue(const QString &newUnitValue)
{
    UnitValue = newUnitValue;
}

const QString &RegUnit::getUnitName() const
{
    return UnitName;
}

void RegUnit::setUnitName(const QString &newUnitName)
{
    UnitName = newUnitName;
}

const QString &RegUnit::getUnitType() const
{
    return UnitType;
}

void RegUnit::setUnitType(const QString &newUnitType)
{
    UnitType = newUnitType;
}

RegUnit::RegUnit()
{

}

RegUnit::RegUnit(QString name, QString value, QString type)
{
    this->UnitName = name;
    this->UnitValue = value;
    this->UnitType = type;
}
