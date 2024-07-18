#include "defaultpath.h"

DefaultPath::DefaultPath()
{
    isContinuous = true;
    firstTime = true;
}

DefaultPicManFigure *DefaultPath::createFigure()
{
    return new DefaultPath();
}

QString DefaultPath::getFigureClassName()
{
    return typeid (this).name();
}

void DefaultPath::PressDrawing(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene,  QColor colorPen, QColor colorBrush, int thickness)
{
    if(firstTime)
    {
        currentColor = colorPen;
        currentThickness = thickness;
    }

    path = new QGraphicsLineItem();
    setExternalImageOfFigure(path);

    QPen pen;
    pen.setWidth(currentThickness);
    pen.setColor(currentColor);
    path->setPen(pen);

    if(firstTime)
    {
        xCoord = event->scenePos().x();
        yCoord = event->scenePos().y();
        path->setLine(xCoord, yCoord, xCoord, yCoord);
    }
    else
        path->setLine(xCoord, yCoord, event->scenePos().x(), event->scenePos().y());

    path->update();
    scene->addItem(path);
    scene->update();
}

void DefaultPath::MoveDrawing(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
{
    path->setLine(xCoord, yCoord, event->scenePos().x(), event->scenePos().y());
    scene->update();
}

void DefaultPath::ReleaseDrawing(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
{
    xCoord = event->scenePos().x();
    yCoord = event->scenePos().y();

    firstTime = false;

    QPoint point;
    point.setX(path->boundingRect().topLeft().x() + (path->boundingRect().bottomRight().x() - path->boundingRect().topLeft().x())/2);
    point.setY(path->boundingRect().topLeft().y() + (path->boundingRect().bottomRight().y() - path->boundingRect().topLeft().y())/2);
    setCenterPoint(point);
}
