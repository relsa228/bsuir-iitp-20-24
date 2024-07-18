#ifndef DEFAULTPATH_H
#define DEFAULTPATH_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

#include "defaultpicmanfigure.h"

class DefaultPath: public DefaultPicManFigure
{
private:
    int xCoord;
    int yCoord;
    QGraphicsLineItem* path;

    QColor currentColor;
    int currentThickness;

public:
    DefaultPath();
    DefaultPicManFigure *createFigure() final;
    QString getFigureClassName() final;

    void PressDrawing(QGraphicsSceneMouseEvent * event, QGraphicsScene *scene, QColor colorPen, QColor colorBrush, int thickness) final;
    void MoveDrawing(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene) final;
    void ReleaseDrawing(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene) final;
};

#endif // DEFAULTPATH_H
