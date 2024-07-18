#ifndef DEFAULTRECTANGLE_H
#define DEFAULTRECTANGLE_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QJsonObject>

#include "defaultpicmanfigure.h"

class DefaultRectangle: public DefaultPicManFigure
{

private:
    int xCoord;
    int yCoord;
    QGraphicsRectItem* rectangle;

public:
    DefaultRectangle();
    DefaultPicManFigure *createFigure() final;
    QString getFigureClassName() final;

    void PressDrawing(QGraphicsSceneMouseEvent * event, QGraphicsScene *scene, QColor colorPen, QColor colorBrush, int thickness) final;
    void MoveDrawing(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene) final;
    void ReleaseDrawing(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene) final;

    QJsonObject SerializeFigure() final;
    DefaultPicManFigure *DeserializeFigure(QJsonObject inObj) final;

    DefaultPicManFigure *CopyItem() final;
};

#endif // DEFAULTRECTANGLE_H
