#include "defaultplot.h"
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

DefaultPlot::DefaultPlot()
{
    isContinuous = true;
    counter = 0;
    polygon = new QGraphicsPolygonItem();
    firstTime = true;
}

DefaultPicManFigure *DefaultPlot::createFigure()
{
    return new DefaultPlot();
}

QString DefaultPlot::getFigureClassName()
{
    return typeid (this).name();
}

void DefaultPlot::PressDrawing(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene, QColor colorPen, QColor colorBrush, int thickness)
{
    setColorBrush(colorBrush);
    setColorPen(colorPen);
    setThickness(thickness);

    QPolygonF polig = polygon->polygon();
    setExternalImageOfFigure(polygon);
    if(firstTime)
    {
        polig << QPointF(event->scenePos().x(), event->scenePos().y());
        firstTime = false;
        currentPenColor = colorPen;
        currentBrushColor = colorBrush;
        currentThickness = thickness;
    }
    polig << QPointF(event->scenePos().x(), event->scenePos().y());
    polygon->setFillRule(Qt::WindingFill);
    polygon->setPolygon(polig);
    counter++;

    QPen pen;
    pen.setWidth(currentThickness);
    pen.setColor(currentPenColor);
    polygon->setPen(pen);
    polygon->setBrush(currentBrushColor);

    polygon->update();
    scene->addItem(polygon);
    scene->update();
}

void DefaultPlot::MoveDrawing(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
{
    QPolygonF polig = polygon->polygon();
    polig[counter] = QPointF(event->scenePos().x(), event->scenePos().y());
    polygon->setPolygon(polig);
    scene->update();
}

void DefaultPlot::ReleaseDrawing(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
{
    QPoint point;
    point.setX(polygon->boundingRect().topLeft().x() + (polygon->boundingRect().bottomRight().x() - polygon->boundingRect().topLeft().x())/2);
    point.setY(polygon->boundingRect().topLeft().y() + (polygon->boundingRect().bottomRight().y() - polygon->boundingRect().topLeft().y())/2);
    setCenterPoint(point);
    setBoundingRect(polygon->boundingRect());
    currentPolygon = polygon->polygon();
}

QJsonObject DefaultPlot::SerializeFigure()
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

DefaultPicManFigure *DefaultPlot::DeserializeFigure(QJsonObject inObj)
{
    DefaultPlot* result = new DefaultPlot();
    QGraphicsPolygonItem* newPlot = new QGraphicsPolygonItem();

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

    newPlot->setBrush(QColor(inObj.value(KEY_COLORBRUSH).toString()));
    newPlot->setPen(pen);
    newPlot->setScale(inObj.value(KEY_SCALE).toInt());
    newPlot->setRotation(inObj.value(KEY_ROTATE).toInt());
    newPlot->setTransformOriginPoint(QPoint(inObj.value(KEY_CENTERPOINT_X).toInt(), inObj.value(KEY_CENTERPOINT_Y).toInt()));
    newPlot->setFillRule(Qt::WindingFill);
    newPlot->setPolygon(polygon);

    result->setBoundingRect(rect);
    result->setCenterPoint(QPoint(inObj.value(KEY_CENTERPOINT_X).toInt(), inObj.value(KEY_CENTERPOINT_Y).toInt()));
    result->setColorBrush(QColor(inObj.value(KEY_COLORBRUSH).toString()));
    result->setColorPen(inObj.value(KEY_COLORPEN).toString());
    result->setExternalImageOfFigure(newPlot);
    result->setThickness(inObj.value(KEY_THICKNESS).toInt());
    result->currentPolygon = polygon;

    return result;
}

DefaultPicManFigure *DefaultPlot::CopyItem()
{
    DefaultPlot* result = new DefaultPlot();
    QGraphicsPolygonItem* newPlot = new QGraphicsPolygonItem();

    QPen pen;
    pen.setWidth(getThickness());
    pen.setColor(getColorPen());

    newPlot->setBrush(getColorBrush());
    newPlot->setPen(pen);
    newPlot->setScale(getExternalImageOfFigure()->scale());
    newPlot->setRotation((getExternalImageOfFigure()->rotation()));
    newPlot->setTransformOriginPoint(getCenterPoint());
    newPlot->setFillRule(Qt::WindingFill);
    newPlot->setPolygon(currentPolygon);

    result->setBoundingRect(getBoundingRect());
    result->setCenterPoint(getCenterPoint());
    result->setColorBrush(getColorBrush());
    result->setColorPen(getColorPen());
    result->setExternalImageOfFigure(newPlot);
    result->setThickness(getThickness());

    return result;
}
