#ifndef FILLTOOL_H
#define FILLTOOL_H

#include <QColor>
#include <QGraphicsItem>
#include <QGraphicsEffect>

class FillTool
{
private:
    QColor targetColor;
public:
    FillTool();

    void setTargetColor(const QColor &newTargetColor);
    void Fill(QGraphicsItem* item, QColor fill_color);
};

#endif // FILLTOOL_H
