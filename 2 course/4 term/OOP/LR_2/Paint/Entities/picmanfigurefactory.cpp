#include "picmanfigurefactory.h"

PicManFigureFactory::PicManFigureFactory()
{
    registrateNewFigure(new DefaultEllipse());
    registrateNewFigure(new DefaultLine());
    registrateNewFigure(new DefaultPath());
    registrateNewFigure(new DefaultPlot());
    registrateNewFigure(new DefaultRectangle());
}

void PicManFigureFactory::registrateNewFigure(DefaultPicManFigure *figure)
{
    const QString stringName = figure->getFigureClassName();
    figureMap.insert(stringName, figure->createFigure());
}

DefaultPicManFigure *PicManFigureFactory::createFigure(QString figureName)
{
    if(figureMap.find(figureName).value() != NULL)
        return figureMap.find(figureName).value()->createFigure();

    return NULL;
}
