#include "eraser.h"

Eraser::Eraser()
{

}

Eraser::~Eraser()
{

}

void Eraser::PressErase(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene, int thickness)
{
    // При нажатии кнопки мыши отрисовываем эллипс
    scene->addEllipse(event->scenePos().x() - 5,
               event->scenePos().y() - 5,
               thickness,
               thickness,
               QPen(Qt::NoPen),
               QBrush(Qt::white));
    // Сохраняем координаты точки нажатия
    previousPoint = event->scenePos();
}

void Eraser::MoveErase(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene, int thickness)
{
    // Отрисовываем линии с использованием предыдущей координаты
    scene->addLine(previousPoint.x(),
            previousPoint.y(),
            event->scenePos().x(),
            event->scenePos().y(),
            QPen(Qt::white,thickness,Qt::SolidLine,Qt::RoundCap));
    // Обновляем данные о предыдущей координате
    previousPoint = event->scenePos();
}
