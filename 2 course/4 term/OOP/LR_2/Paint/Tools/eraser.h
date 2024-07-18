#ifndef ERASER_H
#define ERASER_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QDebug>


class Eraser
{
private:
    QPointF previousPoint;

public:
    explicit Eraser();
    ~Eraser();

    void PressErase(QGraphicsSceneMouseEvent * event, QGraphicsScene *scene, int thickness);
    void MoveErase(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene, int thickness);
};

#endif // ERASER_H
