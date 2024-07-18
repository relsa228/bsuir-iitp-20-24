#ifndef PICMANFIGURESSERIALIZER_H
#define PICMANFIGURESSERIALIZER_H

#include "Entities/picmanfigurefactory.h"
#include <QFile>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonDocument>

#include "defaultpicmanfigure.h"

class PicManFigureSerializer
{
public:
    PicManFigureSerializer();

    bool dump(DefaultPicManFigure* fugure, QString filePath);
    DefaultPicManFigure* load(QString filePath, PicManFigureFactory* factory);
};

#endif // PICMANFIGURESSERIALIZER_H
