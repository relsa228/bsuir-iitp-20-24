#ifndef REGWORKERSERVICE_H
#define REGWORKERSERVICE_H

#include <windows.h>
#include <QFile>
#include <QVector>
#include <sstream>

#include "Entities/regunit.h"

class RegWorkerService
{
private:
    QVector<RegUnit>* getNamesOfUnits(HKEY hKey);
public:
    RegWorkerService();

    RegUnit extractUnit(LPCTSTR subkey, LPCTSTR name, DWORD type, HKEY option);
    QVector<RegUnit>* extractUnits(LPCTSTR subkey, DWORD type, HKEY option);
    void exportSettings(QVector<RegUnit> *units, QString subkey, HKEY hkey, QString filePath);
};

#endif // REGWORKERSERVICE_H
