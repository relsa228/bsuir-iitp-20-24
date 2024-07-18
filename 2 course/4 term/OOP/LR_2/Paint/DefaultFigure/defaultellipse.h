#ifndef DEFAULTELLIPSE_H
#define DEFAULTELLIPSE_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

#include "defaultpicmanfigure.h"

class DefaultEllipse: public DefaultPicManFigure
{
private:
    int xCoord;
    int yCoord;
    QGraphicsEllipseItem* ellipse;

public:
    DefaultEllipse();
    DefaultPicManFigure *createFigure() final;
    QString getFigureClassName() final;

    void PressDrawing(QGraphicsSceneMouseEvent * event, QGraphicsScene *scene, QColor colorPen, QColor colorBrush, int thickness) final;
    void MoveDrawing(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene) final;
    void ReleaseDrawing(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene) final;

    QJsonObject SerializeFigure() final;
    DefaultPicManFigure *DeserializeFigure(QJsonObject inObj) final;

    DefaultPicManFigure *CopyItem() final;
};

#endif // DEFAULTELLIPSE_H
