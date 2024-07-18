#ifndef REGUNIT_H
#define REGUNIT_H

#include <QString>


class RegUnit
{
private:
    QString UnitName;
    QString UnitValue;
    QString UnitType;

public:
    RegUnit();
    RegUnit(QString name, QString value, QString type);
    const QString &getUnitValue() const;
    void setUnitValue(const QString &newUnitValue);
    const QString &getUnitName() const;
    void setUnitName(const QString &newUnitName);
    const QString &getUnitType() const;
    void setUnitType(const QString &newUnitType);
};

#endif // REGUNIT_H
