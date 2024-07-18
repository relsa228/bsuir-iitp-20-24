#ifndef RIGHTTRIANGLE_H
#define RIGHTTRIANGLE_H

#include "RightTriangle_global.h"

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

#include "defaultpicmanfigure.h"

extern "C" RIGHTTRIANGLE_EXPORT DefaultPicManFigure* extractFromLibrary();

class RightTriangle: public DefaultPicManFigure
{
private:
    int xCoord;
    int yCoord;
    QGraphicsPolygonItem* rightTriangle;

    QColor currentPenColor;
    QColor currentBrushColor;
    int currentThickness;
    QPolygonF currentPolygon;

public:
    RightTriangle();
    DefaultPicManFigure *createFigure() final;
    QString getFigureClassName() final;

    void PressDrawing(QGraphicsSceneMouseEvent * event, QGraphicsScene *scene, QColor colorPen, QColor colorBrush, int thickness) final;
    void MoveDrawing(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene) final;
    void ReleaseDrawing(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene) final;

    QJsonObject SerializeFigure() final;
    DefaultPicManFigure *DeserializeFigure(QJsonObject inObj) final;

    DefaultPicManFigure *CopyItem() final;
};

#endif // RIGHTTRIANGLE_H
