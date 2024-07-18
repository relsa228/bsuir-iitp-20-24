#include "defaultellipse.h"

#define KEY_TYPE "Type"
#define KEY_TOPLEFT_X "TopLeft_X"
#define KEY_TOPLEFT_Y "TopLeft_Y"
#define KEY_BOTRIGHT_X "BottomRight_X"
#define KEY_BOTRIGHT_Y "BottomRight_Y"
#define KEY_CENTERPOINT_X "CenterPoint_X"
#define KEY_CENTERPOINT_Y "CenterPoint_Y"
#define KEY_COLORBRUSH "ColorBrush"
#define KEY_COLORPEN "ColorPen"
#define KEY_THICKNESS "Thickness"
#define KEY_ROTATE "Rotate"
#define KEY_SCALE "Scale"

DefaultEllipse::DefaultEllipse()
{
    isContinuous = false;
}

DefaultPicManFigure *DefaultEllipse::createFigure()
{
    return new DefaultEllipse();
}

QString DefaultEllipse::getFigureClassName()
{
    return typeid (this).name();
}

void DefaultEllipse::PressDrawing(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene, QColor colorPen, QColor colorBrush, int thickness)
{
    setColorBrush(colorBrush);
    setColorPen(colorPen);
    setThickness(thickness);

    ellipse = new QGraphicsEllipseItem();
    setExternalImageOfFigure(ellipse);

    QPoint point;
    point.setX(event->scenePos().x());
    point.setY(event->scenePos().y());
    setCenterPoint(point);

    QPen pen;
    pen.setWidth(thickness);
    pen.setColor(colorPen);

    ellipse->setPen(pen);
    ellipse->setBrush(colorBrush);
    ellipse->setRect(event->scenePos().x(), event->scenePos().y(), 0, 0);
    xCoord = event->scenePos().x();
    yCoord = event->scenePos().y();
    ellipse->update();
    scene->addItem(ellipse);
    scene->update();
}

void DefaultEllipse::MoveDrawing(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
{
    ellipse->setRect(xCoord, yCoord, event->scenePos().x() - xCoord, event->scenePos().y() - yCoord);
    scene->update();

    QPoint point;
    point.setX((event->scenePos().x() - xCoord)/2 + xCoord);
    point.setY(abs((yCoord + event->scenePos().y())/2));
    setCenterPoint(point);
}

void DefaultEllipse::ReleaseDrawing(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
{
    QPoint point;
    point.setX(ellipse->boundingRect().topLeft().x() + (ellipse->boundingRect().bottomRight().x() - ellipse->boundingRect().topLeft().x())/2);
    point.setY(ellipse->boundingRect().topLeft().y() + (ellipse->boundingRect().bottomRight().y() - ellipse->boundingRect().topLeft().y())/2);
    setCenterPoint(point);
    setBoundingRect(ellipse->boundingRect());
}

QJsonObject DefaultEllipse::SerializeFigure()
{
    qreal rotate = getExternalImageOfFigure()->rotation();
    qreal scale = getExternalImageOfFigure()->scale();


    QJsonObject serializeObj;
    serializeObj.insert(KEY_TYPE, QJsonValue::fromVariant(typeid (this).name()));
    serializeObj.insert(KEY_TOPLEFT_X, QJsonValue::fromVariant(getBoundingRect().topLeft().x()));
    serializeObj.insert(KEY_TOPLEFT_Y, QJsonValue::fromVariant(getBoundingRect().topLeft().y()));
    serializeObj.insert(KEY_BOTRIGHT_X, QJsonValue::fromVariant(getBoundingRect().bottomRight().x()));
    serializeObj.insert(KEY_BOTRIGHT_Y, QJsonValue::fromVariant(getBoundingRect().bottomRight().y()));
    serializeObj.insert(KEY_CENTERPOINT_X, QJsonValue::fromVariant(getCenterPoint().x()));
    serializeObj.insert(KEY_CENTERPOINT_Y, QJsonValue::fromVariant(getCenterPoint().y()));
    serializeObj.insert(KEY_COLORBRUSH, QJsonValue::fromVariant(getColorBrush()));
    serializeObj.insert(KEY_COLORPEN, QJsonValue::fromVariant(getColorPen()));
    serializeObj.insert(KEY_THICKNESS, QJsonValue::fromVariant(getThickness()));
    serializeObj.insert(KEY_ROTATE, QJsonValue::fromVariant(rotate));
    serializeObj.insert(KEY_SCALE, QJsonValue::fromVariant(scale));

    return serializeObj;
}

DefaultPicManFigure *DefaultEllipse::DeserializeFigure(QJsonObject inObj)
{
    DefaultEllipse* result = new DefaultEllipse();
    QGraphicsEllipseItem* newEllipse = new QGraphicsEllipseItem();

    QPen pen;
    pen.setWidth(inObj.value(KEY_THICKNESS).toInt());
    pen.setColor(inObj.value(KEY_COLORPEN).toString());

    QRectF rect;
    rect.setTopLeft(QPointF(inObj.value(KEY_TOPLEFT_X).toInt(), inObj.value(KEY_TOPLEFT_Y).toInt()));
    rect.setBottomRight(QPointF(inObj.value(KEY_BOTRIGHT_X).toInt(), inObj.value(KEY_BOTRIGHT_Y).toInt()));

    newEllipse->setRect(rect);
    newEllipse->setBrush(QColor(inObj.value(KEY_COLORBRUSH).toString()));
    newEllipse->setPen(pen);
    newEllipse->setScale(inObj.value(KEY_SCALE).toInt());
    newEllipse->setRotation(inObj.value(KEY_ROTATE).toInt());
    newEllipse->setTransformOriginPoint(inObj.value(KEY_CENTERPOINT_X).toInt(), inObj.value(KEY_CENTERPOINT_Y).toInt());

    result->setBoundingRect(rect);
    result->setCenterPoint(QPoint(inObj.value(KEY_CENTERPOINT_X).toInt(), inObj.value(KEY_CENTERPOINT_Y).toInt()));
    result->setColorBrush(inObj.value(KEY_COLORBRUSH).toString());
    result->setColorPen(inObj.value(KEY_COLORPEN).toString());
    result->setExternalImageOfFigure(newEllipse);
    result->setThickness(inObj.value(KEY_THICKNESS).toInt());

    return result;
}

DefaultPicManFigure *DefaultEllipse::CopyItem()
{
    DefaultEllipse* result = new DefaultEllipse();
    QGraphicsEllipseItem* newEllipse = new QGraphicsEllipseItem();

    QPen pen;
    pen.setWidth(getThickness());
    pen.setColor(getColorPen());

    newEllipse->setBrush(getColorBrush());
    newEllipse->setPen(pen);
    newEllipse->setRect(getBoundingRect());
    newEllipse->setScale(getExternalImageOfFigure()->scale());
    newEllipse->setRotation(getExternalImageOfFigure()->rotation());
    newEllipse->setTransformOriginPoint(getCenterPoint());

    result->setBoundingRect(getBoundingRect());
    result->setCenterPoint(getCenterPoint());
    result->setColorBrush(getColorBrush());
    result->setColorPen(getColorPen());
    result->setExternalImageOfFigure(newEllipse);
    result->setThickness(getThickness());

    return result;
}
