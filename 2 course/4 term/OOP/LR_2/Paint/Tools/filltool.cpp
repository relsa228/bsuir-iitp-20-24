#include "filltool.h"

void FillTool::setTargetColor(const QColor &newTargetColor)
{
    targetColor = newTargetColor;
}

void FillTool::Fill(QGraphicsItem* item, QColor fillColor)
{
    QGraphicsColorizeEffect* effect = new QGraphicsColorizeEffect();

    effect->setColor(fillColor);
    item->setGraphicsEffect(effect);
    item->update();
}

FillTool::FillTool()
{

}
