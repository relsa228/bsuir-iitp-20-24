#ifndef PICMANFIGUREFACTORY_H
#define PICMANFIGUREFACTORY_H

#include "DefaultFigure/defaultellipse.h"
#include "DefaultFigure/defaultline.h"
#include "DefaultFigure/defaultpath.h"
#include "DefaultFigure/defaultplot.h"
#include "DefaultFigure/defaultrectangle.h"

#include "defaultpicmanfigure.h"

class PicManFigureFactory
{
private:
    QMap<QString, DefaultPicManFigure*> figureMap;

public:
    PicManFigureFactory();
    DefaultPicManFigure *createFigure(QString figureName);
    void registrateNewFigure(DefaultPicManFigure* figure);
};

#endif // PICMANFIGUREFACTORY_H
