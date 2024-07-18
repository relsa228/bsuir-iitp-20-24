#include "brush.h"

Brush::Brush()
{

}

Brush::~Brush()
{

}

void Brush::PressDrawing(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene, QColor color, int thickness)
{
    scene->addEllipse(event->scenePos().x() - 5,
               event->scenePos().y() - 5,
               thickness,
               thickness,
               QPen(Qt::NoPen),
               QBrush(color));
    previousPoint = event->scenePos();
}

void Brush::MoveDrawing(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene, QColor color, int thickness)
{
    scene->addLine(previousPoint.x(),
            previousPoint.y(),
            event->scenePos().x(),
            event->scenePos().y(),
            QPen(color, thickness, Qt::SolidLine, Qt::RoundCap));
    previousPoint = event->scenePos();
}
