#ifndef DEFAULTPICMANFIGURE_H
#define DEFAULTPICMANFIGURE_H

#include "DefaultPicManFigure_global.h"
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QDataStream>
#include <QJsonObject>

class DEFAULTPICMANFIGURE_EXPORT DefaultPicManFigure
{
private:
    QGraphicsItem* externalImageOfFigure;
    QPoint centerPoint;
    QColor colorPen;
    QColor colorBrush;
    QRectF boundingRect;
    int thickness;

public:
    bool isContinuous;
    bool firstTime;

    DefaultPicManFigure();

    virtual DefaultPicManFigure *createFigure();
    virtual QString getFigureClassName();

    virtual void PressDrawing(QGraphicsSceneMouseEvent * event, QGraphicsScene *scene, QColor colorPen, QColor colorBrush, int thickness);
    virtual void MoveDrawing(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene);
    virtual void ReleaseDrawing(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene);

    virtual QJsonObject SerializeFigure();
    virtual DefaultPicManFigure* DeserializeFigure(QJsonObject inObj);

    virtual DefaultPicManFigure* CopyItem();

    QGraphicsItem *getExternalImageOfFigure() const;
    void setExternalImageOfFigure(QGraphicsItem *newExternalImageOfFigure);
    QPoint getCenterPoint() const;
    void setCenterPoint(QPoint newCenterPoint);
    const QColor &getColorBrush() const;
    void setColorBrush(const QColor &newColorBrush);
    int getThickness() const;
    void setThickness(int newThickness);
    const QColor &getColorPen() const;
    void setColorPen(const QColor &newColorPen);
    const QRectF &getBoundingRect() const;
    void setBoundingRect(const QRectF &newBoundingRect);
};

#endif // DEFAULTPICMANFIGURE_H
