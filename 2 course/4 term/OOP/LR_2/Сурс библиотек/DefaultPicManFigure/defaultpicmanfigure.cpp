#include "defaultpicmanfigure.h"

const QColor &DefaultPicManFigure::getColorBrush() const
{
    return colorBrush;
}

void DefaultPicManFigure::setColorBrush(const QColor &newColorBrush)
{
    colorBrush = newColorBrush;
}

int DefaultPicManFigure::getThickness() const
{
    return thickness;
}

void DefaultPicManFigure::setThickness(int newThickness)
{
    thickness = newThickness;
}

const QColor &DefaultPicManFigure::getColorPen() const
{
    return colorPen;
}

void DefaultPicManFigure::setColorPen(const QColor &newColorPen)
{
    colorPen = newColorPen;
}

const QRectF &DefaultPicManFigure::getBoundingRect() const
{
    return boundingRect;
}

void DefaultPicManFigure::setBoundingRect(const QRectF &newBoundingRect)
{
    boundingRect = newBoundingRect;
}

DefaultPicManFigure::DefaultPicManFigure()
{
    externalImageOfFigure = NULL;
}

DefaultPicManFigure *DefaultPicManFigure::createFigure()
{
    return NULL;
}

QString DefaultPicManFigure::getFigureClassName()
{
    return typeid (this).name();
}

QGraphicsItem *DefaultPicManFigure::getExternalImageOfFigure() const
{
    return externalImageOfFigure;
}

void DefaultPicManFigure::setExternalImageOfFigure(QGraphicsItem *newExternalImageOfFigure)
{
    externalImageOfFigure = newExternalImageOfFigure;
}

QPoint DefaultPicManFigure::getCenterPoint() const
{
    return centerPoint;
}

void DefaultPicManFigure::setCenterPoint(QPoint newCenterPoint)
{
    centerPoint = newCenterPoint;
}

void DefaultPicManFigure::PressDrawing(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene, QColor colorPen, QColor colorBrush, int thickness){}

void DefaultPicManFigure::MoveDrawing(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene){}

void DefaultPicManFigure::ReleaseDrawing(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene){}

QJsonObject DefaultPicManFigure::SerializeFigure(){}

DefaultPicManFigure *DefaultPicManFigure::DeserializeFigure(QJsonObject inObj){}

DefaultPicManFigure *DefaultPicManFigure::CopyItem(){}
