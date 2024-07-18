#ifndef PICMANLIBRARIESEXTRACTER_H
#define PICMANLIBRARIESEXTRACTER_H

#include <QString>
#include <QDir>
#include <QLibrary>
#include <QCoreApplication>
#include <QDebug>

#include <Entities/picmanfigurefactory.h>


class PicManLibrariesExtracter
{
public:
    PicManLibrariesExtracter();

    void updateLibraryList(QStringList *listOfNames, PicManFigureFactory* factory);
};

#endif // PICMANLIBRARIESEXTRACTER_H
