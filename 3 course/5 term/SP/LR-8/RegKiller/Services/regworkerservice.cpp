#include "regworkerservice.h"

#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383

RegWorkerService::RegWorkerService()
{

}

QVector<RegUnit>* RegWorkerService::getNamesOfUnits(HKEY hKey)
{
    QVector<RegUnit>* result = new QVector<RegUnit>();

    TCHAR    achClass[MAX_PATH] = TEXT("");
    DWORD    cchClassName = MAX_PATH;
    DWORD    cSubKeys=0;
    DWORD    cbMaxSubKey;
    DWORD    cchMaxClass;
    DWORD    cValues;
    DWORD    cchMaxValue;
    DWORD    cbMaxValueData;
    DWORD    cbSecurityDescriptor;
    FILETIME ftLastWriteTime;

    DWORD i, retCode;

    TCHAR  achValue[MAX_VALUE_NAME];
    DWORD cchValue = MAX_VALUE_NAME;

    retCode = RegQueryInfoKey(
            hKey,
            achClass,
            &cchClassName,
            NULL,
            &cSubKeys,
            &cbMaxSubKey,
            &cchMaxClass,
            &cValues,
            &cchMaxValue,
            &cbMaxValueData,
            &cbSecurityDescriptor,
            &ftLastWriteTime);

    if (cValues) {
        for (i = 0, retCode = ERROR_SUCCESS; i < cValues; i++) {
            cchValue = MAX_VALUE_NAME;
            achValue[0] = '\0';
            retCode = RegEnumValue(hKey, i,
                                   achValue,
                                   &cchValue, NULL, NULL, NULL, NULL);

            if (retCode == ERROR_SUCCESS) {
                std::wstring test(&achValue[0]);
                std::string name(test.begin(), test.end());
                result->push_back(RegUnit(QString::fromStdString(name), "", ""));
            }
        }
    }

    return result;
}

RegUnit RegWorkerService::extractUnit(LPCTSTR subkey, LPCTSTR name, DWORD type, HKEY option)
{
    HKEY key;
    TCHAR value[255];
    DWORD valueL = 255;
    QString typeStr;
    QString result;
    RegOpenKey(option, subkey, &key);
    RegQueryValueEx(key, name, NULL, &type, (LPBYTE)&value, &valueL);

    if (type == REG_DWORD) {
        DWORD dword;
        if (0 == RegQueryValueEx(key, name, NULL, &type, reinterpret_cast<BYTE*>(&dword), &valueL)) {
            std::stringstream ss;
            ss << dword;
            result = QString::fromStdString(ss.str());
            long long temp = result.toInt();
            result = QString::number(temp, 16);
            if (result.length() < 8) {
                QString nulls = "";
                for (int i = result.length(); i < 8; i++)
                    nulls += "0";
                result = nulls + result;
            }
        }
        typeStr = "REG_DWORD";
    }
    else if (type == REG_SZ) {
        std::wstring test(&value[0]);
        result = QString::fromStdString(std::string(test.begin(), test.end()));
        typeStr = "REG_SZ";
    }

    RegCloseKey(key);

    if(type != REG_DWORD && type != REG_SZ)
        return RegUnit("", "", "");
    return RegUnit(QString::fromWCharArray(name), result, typeStr);
}

QVector<RegUnit> *RegWorkerService::extractUnits(LPCTSTR subkey, DWORD type, HKEY option)
{
    HKEY key;
    RegOpenKey(option, subkey, &key);
    QVector<RegUnit> *result = getNamesOfUnits(key);

    for(int i = 0; i < result->count(); i++) {
        std::wstring inptName = result->at(i).getUnitName().toStdWString();
        RegUnit temp = extractUnit(subkey,inptName.c_str(), type, option);
        if (temp.getUnitType() != "")
            (*result)[i] = temp;
        else{
            result->remove(i);
            i--;
        }
    }

    return result;
}

void RegWorkerService::exportSettings(QVector<RegUnit> *units, QString subkey, HKEY hkey, QString filePath)
{
    QString exportSettings ="[";

    if (hkey == HKEY_CLASSES_ROOT)
        exportSettings += "HKEY_CLASSES_ROOT\\";
    if (hkey == HKEY_CURRENT_USER)
        exportSettings += "HKEY_CURRENT_USER\\";
    if (hkey == HKEY_LOCAL_MACHINE)
        exportSettings += "HKEY_LOCAL_MACHINE\\";
    if (hkey == HKEY_USERS)
        exportSettings += "HKEY_USERS";
    if (hkey == HKEY_CURRENT_CONFIG)
        exportSettings += "HKEY_CURRENT_CONFIG\\";

    exportSettings += subkey + "]\n";

    for(auto unit: *units) {
        exportSettings += "\"" + unit.getUnitName() + "\"=";
        if(unit.getUnitType() == "REG_SZ")
            exportSettings += "\"" + unit.getUnitValue() + "\"\n";
        if(unit.getUnitType() == "REG_DWORD")
            exportSettings += "dword:" + unit.getUnitValue() + "\n";
    }

    QFile outFile(filePath);

    if(!outFile.open(QIODevice::WriteOnly))
        return;

    outFile.write(exportSettings.toUtf8());
    outFile.flush();
    outFile.close();
}
