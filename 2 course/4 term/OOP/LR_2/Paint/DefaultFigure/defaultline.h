#ifndef DEFAULTLINE_H
#define DEFAULTLINE_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

#include "defaultpicmanfigure.h"

class DefaultLine: public DefaultPicManFigure
{
private:
    int xCoord;
    int yCoord;
    QGraphicsLineItem* line;

public:
    DefaultLine();
    DefaultPicManFigure *createFigure() final;
    QString getFigureClassName() final;

    void PressDrawing(QGraphicsSceneMouseEvent * event, QGraphicsScene *scene, QColor colorPen, QColor colorBrush, int thickness) final;
    void MoveDrawing(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene) final;
    void ReleaseDrawing(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene) final;

    QJsonObject SerializeFigure() final;
    DefaultPicManFigure *DeserializeFigure(QJsonObject inObj) final;

    DefaultPicManFigure *CopyItem() final;
};

#endif // DEFAULTLINE_H
