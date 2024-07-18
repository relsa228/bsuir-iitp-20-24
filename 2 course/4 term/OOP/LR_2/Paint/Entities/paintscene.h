//Легенда для инструментов
//0. Курсор
//1. Кисть
//2. Стёрка
//3. Заливка
//4. Фигура

#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QPainter>
#include <QTimer>
#include <QDebug>
#include <QCursor>

#include "Tools/brush.h"
#include "Tools/eraser.h"
#include "Tools/filltool.h"

#include "Entities/picmanfiguresserializer.h"
#include "Entities/picmanfigurefactory.h"
#include "Entities/picmanlibrariesextracter.h"

#include "defaultpicmanfigure.h"

class PaintScene: public QGraphicsScene
{
private:
    int currentThickness;
    QColor currentPenColor;
    QColor currentBrushColor;

    PicManFigureFactory *factory;
    PicManLibrariesExtracter *extracter;

    // Инструменты
    int targetTool;
    Brush brush;
    Eraser eraser;
    FillTool fillTool;
    PicManFigureSerializer serializer;

    DefaultPicManFigure* currentFigure;
    DefaultPicManFigure* loadFigure;

    QVector<QPoint> centerPointsVector;
    QVector<DefaultPicManFigure*> figuresVector;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

public:
    QStringList *namesOfPlugins;
    explicit PaintScene(QObject *parent = 0);
    ~PaintScene();

    void setTargetTool(int newTargetTool);
    void setCurrentPenColor(const QColor &newCurrentColor);
    void setCurrentThickness(int newCurrentThickness);
    void setCurrentFigure(QString figureName);
    void setCurrentBrushColor(const QColor &newCurrentBrushColor);
    int getCurrentThickness() const;

    void rotate(int rotate);
    void zoom(qreal scaleVal);
    void deleteItem();
    void copyItem(QGraphicsSceneMouseEvent *event);
    void undo();
    void redo();
    void dump(QString filePath);
    void load(QString filePath);
};
#endif // PAINTSCENE_H
