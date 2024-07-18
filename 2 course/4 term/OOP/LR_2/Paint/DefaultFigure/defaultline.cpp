#include "defaultline.h"

#define KEY_TYPE "Type"
#define KEY_TOPLEFT_X "TopLeft_X"
#define KEY_TOPLEFT_Y "TopLeft_Y"
#define KEY_BOTRIGHT_X "BottomRight_X"
#define KEY_BOTRIGHT_Y "BottomRight_Y"
#define KEY_CENTERPOINT_X "CenterPoint_X"
#define KEY_CENTERPOINT_Y "CenterPoint_Y"
#define KEY_COLORPEN "ColorPen"
#define KEY_THICKNESS "Thickness"
#define KEY_ROTATE "Rotate"
#define KEY_SCALE "Scale"

DefaultLine::DefaultLine()
{
    isContinuous = false;
}

DefaultPicManFigure *DefaultLine::createFigure()
{
    return new DefaultLine();
}

QString DefaultLine::getFigureClassName()
{
    return typeid (this).name();
}

void DefaultLine::PressDrawing(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene, QColor colorPen, QColor colorBrush, int thickness)
{
    setColorBrush(colorBrush);
    setColorPen(colorPen);
    setThickness(thickness);

    line = new QGraphicsLineItem();
    setExternalImageOfFigure(line);

    QPen pen;
    pen.setWidth(thickness);
    pen.setColor(colorPen);

    line->setPen(pen);
    line->setLine(event->scenePos().x(), event->scenePos().y(), event->scenePos().x(), event->scenePos().y());
    xCoord = event->scenePos().x();
    yCoord = event->scenePos().y();
    line->update();
    scene->addItem(line);
    scene->update();
}

void DefaultLine::MoveDrawing(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
{
    line->setLine(xCoord, yCoord, event->scenePos().x(), event->scenePos().y());
    scene->update();
}

void DefaultLine::ReleaseDrawing(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
{
    QPoint point;
    point.setX(line->boundingRect().topLeft().x() + (line->boundingRect().bottomRight().x() - line->boundingRect().topLeft().x())/2);
    point.setY(line->boundingRect().topLeft().y() + (line->boundingRect().bottomRight().y() - line->boundingRect().topLeft().y())/2);
    setCenterPoint(point);
    setBoundingRect(line->boundingRect());
}

DefaultPicManFigure *DefaultLine::CopyItem()
{
    DefaultLine* result = new DefaultLine();
    QGraphicsLineItem* newLine = new QGraphicsLineItem();

    QPen pen;
    pen.setWidth(getThickness());
    pen.setColor(getColorPen());

    QRectF rect = getBoundingRect();

    newLine->setPen(pen);
    newLine->setScale(getExternalImageOfFigure()->scale());
    newLine->setRotation(getExternalImageOfFigure()->rotation());
    newLine->setTransformOriginPoint(getCenterPoint());
    newLine->setLine(rect.topLeft().x(), rect.topLeft().y(), rect.bottomRight().x(), rect.bottomRight().y());
    //newRectangle->setGraphicsEffect(graphicEffect);

    result->setBoundingRect(getBoundingRect());
    result->setCenterPoint(getCenterPoint());
    result->setColorBrush(getColorBrush());
    result->setColorPen(getColorPen());
    result->setExternalImageOfFigure(newLine);
    result->setThickness(getThickness());

    return result;
}

QJsonObject DefaultLine::SerializeFigure()
{
    qreal rotate = getExternalImageOfFigure()->rotation();
    qreal scale = getExternalImageOfFigure()->scale();

    QJsonObject serializeObj;
    serializeObj.insert(KEY_TYPE, QJsonValue::fromVariant(typeid (this).name()));
    serializeObj.insert(KEY_TOPLEFT_X, QJsonValue::fromVariant((int)getBoundingRect().topLeft().x()));
    serializeObj.insert(KEY_TOPLEFT_Y, QJsonValue::fromVariant((int)getBoundingRect().topLeft().y()));
    serializeObj.insert(KEY_BOTRIGHT_X, QJsonValue::fromVariant((int)getBoundingRect().bottomRight().x()));
    serializeObj.insert(KEY_BOTRIGHT_Y, QJsonValue::fromVariant((int)getBoundingRect().bottomRight().y()));
    serializeObj.insert(KEY_CENTERPOINT_X, QJsonValue::fromVariant((int)getCenterPoint().x()));
    serializeObj.insert(KEY_CENTERPOINT_Y, QJsonValue::fromVariant((int)getCenterPoint().y()));
    serializeObj.insert(KEY_COLORPEN, QJsonValue::fromVariant(getColorPen()));
    serializeObj.insert(KEY_THICKNESS, QJsonValue::fromVariant(getThickness()));
    serializeObj.insert(KEY_ROTATE, QJsonValue::fromVariant(rotate));
    serializeObj.insert(KEY_SCALE, QJsonValue::fromVariant(scale));

    return serializeObj;
}

DefaultPicManFigure *DefaultLine::DeserializeFigure(QJsonObject inObj)
{
    DefaultLine* result = new DefaultLine();
    QGraphicsLineItem* newLine = new QGraphicsLineItem();

    QPen pen;
    pen.setWidth(inObj.value(KEY_THICKNESS).toInt());
    pen.setColor(inObj.value(KEY_COLORPEN).toString());

    QRectF rect;
    rect.setTopLeft(QPointF(inObj.value(KEY_TOPLEFT_X).toInt(), inObj.value(KEY_TOPLEFT_Y).toInt()));
    rect.setBottomRight(QPointF(inObj.value(KEY_BOTRIGHT_X).toInt(), inObj.value(KEY_BOTRIGHT_Y).toInt()));

    newLine->setPen(pen);
    newLine->setScale(inObj.value(KEY_SCALE).toInt());
    newLine->setRotation(inObj.value(KEY_ROTATE).toInt());
    newLine->setTransformOriginPoint(inObj.value(KEY_CENTERPOINT_X).toInt(), inObj.value(KEY_CENTERPOINT_Y).toInt());
    newLine->setLine(rect.bottomRight().x(), rect.bottomRight().y(), rect.topLeft().x(), rect.topLeft().y());

    result->setBoundingRect(rect);
    result->setCenterPoint(QPoint(inObj.value(KEY_CENTERPOINT_X).toInt(), inObj.value(KEY_CENTERPOINT_Y).toInt()));
    result->setColorPen(inObj.value(KEY_COLORPEN).toString());
    result->setExternalImageOfFigure(newLine);
    result->setThickness(inObj.value(KEY_THICKNESS).toInt());

    return result;
}
