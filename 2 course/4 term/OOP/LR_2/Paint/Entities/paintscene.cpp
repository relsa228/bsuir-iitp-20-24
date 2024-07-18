#include "paintscene.h"

PaintScene::PaintScene(QObject *parent) : QGraphicsScene(parent)
{
    targetTool = 0;
    currentFigure = NULL;

    factory = new PicManFigureFactory();
    extracter = new PicManLibrariesExtracter();
    namesOfPlugins = new QStringList();

    extracter->updateLibraryList(namesOfPlugins, factory);
}

PaintScene::~PaintScene()
{

}

void PaintScene::setTargetTool(int newTargetTool)
{
    targetTool = newTargetTool;
}

void PaintScene::setCurrentPenColor(const QColor &newCurrentColor)
{
    currentPenColor = newCurrentColor;
}

void PaintScene::setCurrentBrushColor(const QColor &newCurrentBrushColor)
{
    currentBrushColor = newCurrentBrushColor;
}

void PaintScene::setCurrentThickness(int newCurrentThickness)
{
    currentThickness = newCurrentThickness;
}

void PaintScene::setCurrentFigure(QString figureName)
{
    currentFigure = factory->createFigure(figureName);
    if(currentFigure != NULL)
    {
        figuresVector.push_front(currentFigure);
        targetTool = 4;
    }
}

int PaintScene::getCurrentThickness() const
{
    return currentThickness;
}

void PaintScene::rotate(int rotate)
{
    if(currentFigure != NULL && currentFigure->getExternalImageOfFigure() != NULL)
    {
        currentFigure->getExternalImageOfFigure()->setTransformOriginPoint(currentFigure->getCenterPoint());
        currentFigure->getExternalImageOfFigure()->setRotation(currentFigure->getExternalImageOfFigure()->rotation() + rotate);
        update();
    }
}

void PaintScene::zoom(qreal scaleVal)
{
    if(currentFigure != NULL && currentFigure->getExternalImageOfFigure() != NULL)
    {
        currentFigure->getExternalImageOfFigure()->setTransformOriginPoint(currentFigure->getCenterPoint());
        qreal scale = currentFigure->getExternalImageOfFigure()->scale() + scaleVal;
        if(scale > 0.11 && scale <= 3)
            currentFigure->getExternalImageOfFigure()->setScale(scale);

        update();
    }
}

void PaintScene::deleteItem()
{
    if(currentFigure != NULL && currentFigure->getExternalImageOfFigure()->isVisible())
        currentFigure->getExternalImageOfFigure()->setVisible(false);
}

void PaintScene::copyItem(QGraphicsSceneMouseEvent *event)
{
    DefaultPicManFigure* picmanFigure = currentFigure->CopyItem();
    figuresVector.push_front(picmanFigure);
    picmanFigure->getExternalImageOfFigure()->setPos(event->scenePos().x() - currentFigure->getCenterPoint().x(),
                                                     event->scenePos().y() - currentFigure->getCenterPoint().y());
    centerPointsVector.push_front(picmanFigure->getCenterPoint());
    addItem(picmanFigure->getExternalImageOfFigure());
    update();
}

void PaintScene::undo()
{
    foreach(QGraphicsItem* item, items())
    {
        if(item->isVisible())
        {
            item->setVisible(false);
            if(currentFigure != NULL && !currentFigure->getExternalImageOfFigure()->isVisible())
                currentFigure = NULL;
            break;
        }
    }
}

void PaintScene::redo()
{
    for(int i = items().length() - 1; i > -1; i--)
    {
        if(!items().at(i)->isVisible())
        {
            items().at(i)->setVisible(true);
            break;
        }
    }
}

void PaintScene::dump(QString filePath)
{
    if(currentFigure != NULL)
        serializer.dump(currentFigure, filePath);
}

void PaintScene::load(QString filePath)
{
    DefaultPicManFigure* picmanFigure = serializer.load(filePath, factory);
    loadFigure = picmanFigure;
    targetTool = 6;
}

void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPoint brPoint;
    brPoint.setX(NULL);

    if(targetTool == 0)
    {
        QPointF find;
        find.setX(event->scenePos().x());
        find.setY(event->scenePos().y());
        QList<QGraphicsItem *> temp = items(find);

        if(!temp.isEmpty())
        {
            int chk = NULL;

            for(int i = 0; i < items().length(); i++)
            {
                chk = centerPointsVector.at(i).x();
                if(items().at(i) == temp.at(0) && items().at(i)->isVisible() && chk != NULL)
                    currentFigure = figuresVector.at(i);

                update();
            }

            if(chk == NULL)
                currentFigure = NULL;
        }
    }
    if(targetTool == 1)
    {
        brush.PressDrawing(event, this, currentPenColor, currentThickness);
        centerPointsVector.push_front(brPoint);
    }
    if(targetTool == 2)
    {
        eraser.PressErase(event, this, currentThickness);
        centerPointsVector.push_front(brPoint);
    }
    if(targetTool == 3)
    {
        QPointF find;
        find.setX(event->scenePos().x());
        find.setY(event->scenePos().y());
        QList<QGraphicsItem *> temp = items(find);

        if(!temp.isEmpty())
        {
            for(int i = 0; i < items().length(); i++)
            {
                if(items().at(i) == temp.at(0) && items().at(i)->isVisible() && centerPointsVector.at(i).x() != NULL)
                {
                    fillTool.Fill(items().at(i), currentBrushColor);
                    break;
                }
                update();
            }   
        }
    }
    if(targetTool == 4)
    {
        currentFigure->PressDrawing(event, this, currentPenColor, currentBrushColor, currentThickness);
        update();
    }
    if(targetTool == 5)
        copyItem(event);

    if(targetTool == 6)
    {
        figuresVector.push_front(loadFigure);
        loadFigure->getExternalImageOfFigure()->setPos(event->scenePos().x() - loadFigure->getCenterPoint().x(),
                                                         event->scenePos().y() - loadFigure->getCenterPoint().y());
        centerPointsVector.push_front(loadFigure->getCenterPoint());
        addItem(loadFigure->getExternalImageOfFigure());
        update();
        currentFigure = loadFigure;
        targetTool = 0;
    }
}

void PaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPoint brPoint;

    if(targetTool == 0)
    {
        if(currentFigure != NULL)
            currentFigure->getExternalImageOfFigure()->setPos(event->scenePos().x() - currentFigure->getCenterPoint().x(),
                                                              event->scenePos().y() - currentFigure->getCenterPoint().y());
        update();
    }
    if(targetTool == 1)
    {
        brush.MoveDrawing(event, this, currentPenColor, currentThickness);
        centerPointsVector.push_front(brPoint);
    }
    if(targetTool == 2)
    {
        eraser.MoveErase(event, this, currentThickness);
        centerPointsVector.push_front(brPoint);
    }
    if(targetTool == 4)
    {
        currentFigure->MoveDrawing(event, this);
        update();
    }
}

void PaintScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(targetTool == 4)
    {
        currentFigure->ReleaseDrawing(event, this);
        centerPointsVector.push_front(currentFigure->getCenterPoint());
        if(!currentFigure->isContinuous)
            targetTool = 0;
        update();
    }
}
