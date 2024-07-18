#include "righttriangle.h"
#include <QGraphicsPolygonItem>
#include <QPolygonF>

#define KEY_TYPE "Type"
#define KEY_POLYGON_X "Polygon_point_X_"
#define KEY_POLYGON_Y "Polygon_point_Y_"
#define KEY_CENTERPOINT_X "CenterPoint_X"
#define KEY_CENTERPOINT_Y "CenterPoint_Y"
#define KEY_TOPLEFT_X "TopLeft_X"
#define KEY_TOPLEFT_Y "TopLeft_Y"
#define KEY_BOTRIGHT_X "BottomRight_X"
#define KEY_BOTRIGHT_Y "BottomRight_Y"
#define KEY_COLORBRUSH "ColorBrush"
#define KEY_COLORPEN "ColorPen"
#define KEY_THICKNESS "Thickness"
#define KEY_ROTATE "Rotate"
#define KEY_SCALE "Scale"

extern "C" RIGHTTRIANGLE_EXPORT DefaultPicManFigure* extractFromLibrary()
{
    return new RightTriangle();
}

RightTriangle::RightTriangle()
{
    isContinuous = false;
    rightTriangle = new QGraphicsPolygonItem();
}

DefaultPicManFigure *RightTriangle::createFigure()
{
    return new RightTriangle();
}

QString RightTriangle::getFigureClassName()
{
    return typeid (this).name();
}

void RightTriangle::PressDrawing(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene, QColor colorPen, QColor colorBrush, int thickness)
{
    setColorBrush(colorBrush);
    setColorPen(colorPen);
    setThickness(thickness);

    currentPenColor = colorPen;
    currentBrushColor = colorBrush;
    currentThickness = thickness;

    QPolygonF polig = rightTriangle->polygon();
    setExternalImageOfFigure(rightTriangle);
    polig << QPointF(event->scenePos()) << QPointF(event->scenePos()) << QPointF(event->scenePos());
    rightTriangle->setFillRule(Qt::WindingFill);
    rightTriangle->setPolygon(polig);

    QPen pen;
    pen.setWidth(currentThickness);
    pen.setColor(currentPenColor);
    rightTriangle->setPen(pen);
    rightTriangle->setBrush(currentBrushColor);

    rightTriangle->update();
    scene->addItem(rightTriangle);
    scene->update();

    xCoord = event->scenePos().x();
    yCoord = event->scenePos().y();
}

void RightTriangle::MoveDrawing(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
{
    QPolygonF polig;
    polig << QPointF(xCoord, event->scenePos().y()) << QPointF(event->scenePos().x(), yCoord) << QPointF(event->scenePos());

    rightTriangle->setPolygon(polig);
    scene->update();
}

void RightTriangle::ReleaseDrawing(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
{
    QPoint point;
    point.setX(rightTriangle->boundingRect().topLeft().x() + (rightTriangle->boundingRect().bottomRight().x() - rightTriangle->boundingRect().topLeft().x())/2);
    point.setY(rightTriangle->boundingRect().topLeft().y() + (rightTriangle->boundingRect().bottomRight().y() - rightTriangle->boundingRect().topLeft().y())/2);
    setCenterPoint(point);
    setBoundingRect(rightTriangle->boundingRect());
    currentPolygon = rightTriangle->polygon();
}

QJsonObject RightTriangle::SerializeFigure()
{
    qreal rotate = getExternalImageOfFigure()->rotation();
    qreal scale = getExternalImageOfFigure()->scale();

    QJsonObject serializeObj;
    serializeObj.insert(KEY_TYPE, QJsonValue::fromVariant(typeid (this).name()));

    int i = 0;
    foreach(QPointF point, currentPolygon)
    {
        serializeObj.insert(KEY_POLYGON_X + QString::number(i), QJsonValue::fromVariant(point.x()));
        serializeObj.insert(KEY_POLYGON_Y + QString::number(i), QJsonValue::fromVariant(point.y()));
        i++;
    }
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

DefaultPicManFigure *RightTriangle::DeserializeFigure(QJsonObject inObj)
{
    RightTriangle* result = new RightTriangle();
    QGraphicsPolygonItem *newRightTriangle = new QGraphicsPolygonItem();

    QPen pen;
    pen.setWidth(inObj.value(KEY_THICKNESS).toInt());
    pen.setColor(inObj.value(KEY_COLORPEN).toString());

    QPolygonF polygon;
    for(int i = 0; i < inObj.length(); i++)
    {
        if(inObj.value(KEY_POLYGON_X + QString::number(i)).toInt() == 0)
            break;
        polygon << QPoint(inObj.value(KEY_POLYGON_X + QString::number(i)).toInt(), inObj.value(KEY_POLYGON_Y + QString::number(i)).toInt());
    }

    QRectF rect;
    rect.setTopLeft(QPointF(inObj.value(KEY_TOPLEFT_X).toInt(), inObj.value(KEY_TOPLEFT_Y).toInt()));
    rect.setBottomRight(QPointF(inObj.value(KEY_BOTRIGHT_X).toInt(), inObj.value(KEY_BOTRIGHT_Y).toInt()));

    newRightTriangle->setBrush(QColor(inObj.value(KEY_COLORBRUSH).toString()));
    newRightTriangle->setPen(pen);
    newRightTriangle->setScale(inObj.value(KEY_SCALE).toInt());
    newRightTriangle->setRotation(inObj.value(KEY_ROTATE).toInt());
    newRightTriangle->setTransformOriginPoint(QPoint(inObj.value(KEY_CENTERPOINT_X).toInt(), inObj.value(KEY_CENTERPOINT_Y).toInt()));
    newRightTriangle->setFillRule(Qt::WindingFill);
    newRightTriangle->setPolygon(polygon);

    result->setBoundingRect(rect);
    result->setCenterPoint(QPoint(inObj.value(KEY_CENTERPOINT_X).toInt(), inObj.value(KEY_CENTERPOINT_Y).toInt()));
    result->setColorBrush(QColor(inObj.value(KEY_COLORBRUSH).toString()));
    result->setColorPen(inObj.value(KEY_COLORPEN).toString());
    result->setExternalImageOfFigure(newRightTriangle);
    result->setThickness(inObj.value(KEY_THICKNESS).toInt());
    result->currentPolygon = polygon;

    return result;
}

DefaultPicManFigure *RightTriangle::CopyItem()
{
    RightTriangle *result = new RightTriangle();
    QGraphicsPolygonItem *newRightTriangle = new QGraphicsPolygonItem();

    QPen pen;
    pen.setWidth(getThickness());
    pen.setColor(getColorPen());

    newRightTriangle->setBrush(getColorBrush());
    newRightTriangle->setPen(pen);
    newRightTriangle->setScale(getExternalImageOfFigure()->scale());
    newRightTriangle->setRotation((getExternalImageOfFigure()->rotation()));
    newRightTriangle->setTransformOriginPoint(getCenterPoint());
    newRightTriangle->setFillRule(Qt::WindingFill);
    newRightTriangle->setPolygon(currentPolygon);

    result->setBoundingRect(getBoundingRect());
    result->setCenterPoint(getCenterPoint());
    result->setColorBrush(getColorBrush());
    result->setColorPen(getColorPen());
    result->setExternalImageOfFigure(newRightTriangle);
    result->setThickness(getThickness());

    return result;
}

