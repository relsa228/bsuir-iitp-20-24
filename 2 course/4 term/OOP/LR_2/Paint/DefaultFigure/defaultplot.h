#ifndef DEFAULTPLOT_H
#define DEFAULTPLOT_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

#include "defaultpicmanfigure.h"

class DefaultPlot: public DefaultPicManFigure
{
private:
    int counter;
    bool firstTime;
    QGraphicsPolygonItem* polygon;

    QColor currentPenColor;
    QColor currentBrushColor;
    int currentThickness;
    QPolygonF currentPolygon;

public:
    DefaultPlot();
    DefaultPicManFigure *createFigure() final;
    QString getFigureClassName() final;

    void PressDrawing(QGraphicsSceneMouseEvent * event, QGraphicsScene *scene, QColor colorPen, QColor colorBrush, int thickness) final;
    void MoveDrawing(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene) final;
    void ReleaseDrawing(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene) final;

    QJsonObject SerializeFigure() final;
    DefaultPicManFigure *DeserializeFigure(QJsonObject inObj) final;

    DefaultPicManFigure *CopyItem() final;
};

#endif // DEFAULTPLOT_H
