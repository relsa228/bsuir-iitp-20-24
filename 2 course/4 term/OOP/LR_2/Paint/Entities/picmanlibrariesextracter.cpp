#include "picmanlibrariesextracter.h"

PicManLibrariesExtracter::PicManLibrariesExtracter()
{

}

void PicManLibrariesExtracter::updateLibraryList(QStringList *listOfNames, PicManFigureFactory *factory)
{
    QDir dir;
    dir = dir.absolutePath() + "/debug/Plugins";
    QStringList libsDir = dir.entryList();
    if(!libsDir.isEmpty())
    {
        libsDir.pop_front();
        libsDir.pop_front();

        foreach(QString libPath, libsDir)
        {
            QLibrary library(dir.absoluteFilePath(libPath));
            if(library.load())
            {
                typedef DefaultPicManFigure* (*ExtractFunction)();
                ExtractFunction extractFromLibrary = (ExtractFunction) library.resolve("extractFromLibrary");

                if(extractFromLibrary)
                {
                    DefaultPicManFigure* extractedFigure = extractFromLibrary();
                    factory->registrateNewFigure(extractedFigure);
                    listOfNames->push_back(extractedFigure->getFigureClassName());
                }
            }
        }
    }
}
