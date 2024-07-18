#include "defaultrectangle.h"

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

DefaultRectangle::DefaultRectangle()
{
    isContinuous = false;
}

DefaultPicManFigure *DefaultRectangle::createFigure()
{
    return new DefaultRectangle();
}

QString DefaultRectangle::getFigureClassName()
{
    return typeid (this).name();
}

void DefaultRectangle::PressDrawing(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene, QColor colorPen, QColor colorBrush, int thickness)
{
    setColorBrush(colorBrush);
    setColorPen(colorPen);
    setThickness(thickness);

    rectangle = new QGraphicsRectItem();
    setExternalImageOfFigure(rectangle);

    QPen pen;
    pen.setWidth(thickness);
    pen.setColor(colorPen);

    rectangle->setBrush(colorBrush);
    rectangle->setPen(pen);
    rectangle->setRect(event->scenePos().x(), event->scenePos().y(),1,1);
    xCoord = event->scenePos().x();
    yCoord = event->scenePos().y();
    rectangle->update();
    scene->addItem(rectangle);
    scene->update();
}

void DefaultRectangle::MoveDrawing(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
{
    rectangle->setRect(xCoord, yCoord, event->scenePos().x() - xCoord, event->scenePos().y() - yCoord);
    rectangle->setTransformOriginPoint(xCoord, yCoord);
    scene->update();
}

void DefaultRectangle::ReleaseDrawing(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
{
    QPoint point;
    point.setX(rectangle->boundingRect().topLeft().x() + (rectangle->boundingRect().bottomRight().x() - rectangle->boundingRect().topLeft().x())/2);
    point.setY(rectangle->boundingRect().topLeft().y() + (rectangle->boundingRect().bottomRight().y() - rectangle->boundingRect().topLeft().y())/2);
    setCenterPoint(point);

    setBoundingRect(rectangle->boundingRect());
}

QJsonObject DefaultRectangle::SerializeFigure()
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

DefaultPicManFigure *DefaultRectangle::DeserializeFigure(QJsonObject inObj)
{
    DefaultRectangle* result = new DefaultRectangle();
    QGraphicsRectItem* newRectangle = new QGraphicsRectItem();

    QPen pen;
    pen.setWidth(inObj.value(KEY_THICKNESS).toInt());
    pen.setColor(inObj.value(KEY_COLORPEN).toString());

    QRectF rect;
    rect.setTopLeft(QPointF(inObj.value(KEY_TOPLEFT_X).toInt(), inObj.value(KEY_TOPLEFT_Y).toInt()));
    rect.setBottomRight(QPointF(inObj.value(KEY_BOTRIGHT_X).toInt(), inObj.value(KEY_BOTRIGHT_Y).toInt()));

    newRectangle->setRect(rect);
    newRectangle->setBrush(QColor(inObj.value(KEY_COLORBRUSH).toString()));
    newRectangle->setPen(pen);
    newRectangle->setScale(inObj.value(KEY_SCALE).toInt());
    newRectangle->setRotation(inObj.value(KEY_ROTATE).toInt());
    newRectangle->setTransformOriginPoint(inObj.value(KEY_CENTERPOINT_X).toInt(), inObj.value(KEY_CENTERPOINT_Y).toInt());

    result->setBoundingRect(rect);
    result->setCenterPoint(QPoint(inObj.value(KEY_CENTERPOINT_X).toInt(), inObj.value(KEY_CENTERPOINT_Y).toInt()));
    result->setColorBrush(inObj.value(KEY_COLORBRUSH).toString());
    result->setColorPen(inObj.value(KEY_COLORPEN).toString());
    result->setExternalImageOfFigure(newRectangle);
    result->setThickness(inObj.value(KEY_THICKNESS).toInt());

    return result;
}

DefaultPicManFigure *DefaultRectangle::CopyItem()
{
    DefaultRectangle* result = new DefaultRectangle();
    QGraphicsRectItem* newRectangle = new QGraphicsRectItem();

    QPen pen;
    pen.setWidth(getThickness());
    pen.setColor(getColorPen());

    newRectangle->setBrush(getColorBrush());
    newRectangle->setPen(pen);
    newRectangle->setRect(getBoundingRect());
    newRectangle->setScale(getExternalImageOfFigure()->scale());
    newRectangle->setRotation((getExternalImageOfFigure()->rotation()));
    newRectangle->setTransformOriginPoint(getCenterPoint());
    newRectangle->setGraphicsEffect(getExternalImageOfFigure()->graphicsEffect());

    result->setBoundingRect(getBoundingRect());
    result->setCenterPoint(getCenterPoint());
    result->setColorBrush(getColorBrush());
    result->setColorPen(getColorPen());
    result->setExternalImageOfFigure(newRectangle);
    result->setThickness(getThickness());

    return result;
}
