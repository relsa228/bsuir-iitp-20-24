#ifndef BRUSH_H
#define BRUSH_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QDebug>


class Brush
{
public:
    explicit Brush();
    ~Brush();

private:
    QPointF previousPoint;

public:
    void PressDrawing(QGraphicsSceneMouseEvent * event, QGraphicsScene *scene, QColor color, int thickness);
    void MoveDrawing(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene, QColor color, int thickness);
};

#endif // BRUSH_H
