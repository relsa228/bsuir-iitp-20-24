#ifndef DRAWINGWINDOW_H
#define DRAWINGWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QWidget>
#include <QTimer>
#include <QResizeEvent>
#include <QColorDialog>
#include <QFileDialog>
#include <QGraphicsRectItem>

#include "Entities/paintscene.h"
#include "Entities/picmanfiguresserializer.h"

#include "Forms/thicknessform.h"
#include "Forms/customwindow.h"

#include "DefaultFigure/defaultellipse.h"
#include "DefaultFigure/defaultline.h"
#include "DefaultFigure/defaultpath.h"
#include "DefaultFigure/defaultplot.h"
#include "DefaultFigure/defaultrectangle.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DrawingWindow; }
QT_END_NAMESPACE

class DrawingWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DrawingWindow(QWidget *parent = nullptr);
    ~DrawingWindow();

private:
    Ui::DrawingWindow *ui;
    QTimer *timer;

    PaintScene *paintScene;
    QColorDialog *colorDialog;
    QColor color;
    QColor colorBrush;
    int currentRotate;

private:
    void resizeEvent(QResizeEvent * event);
    void ErrorMsg(QString message);

private slots:
    void slotTimer();
    void on_EraserButton_clicked();
    void on_BrushButton_clicked();
    void on_ColorButton_clicked();
    void on_ThicknessButton_clicked();
    void on_SaveButton_clicked();
    void on_UploadButton_clicked();
    void on_CircleButton_clicked();
    void on_RotateRightButton_clicked();
    void on_RotateLeftButton_clicked();
    void on_RectangleButton_clicked();
    void on_RotateSlider_sliderMoved(int position);
    void on_LineButton_clicked();
    void on_moveButton_clicked();
    void on_CurveButton_clicked();
    void on_HexagonButton_clicked();
    void on_zoomButton_clicked();
    void on_unzoomButton_clicked();
    void on_FillButton_clicked();
    void on_UndoButton_clicked();
    void on_RedoButton_clicked();
    void on_delButton_clicked();
    void on_copyButton_clicked();
    void on_serializeButton_clicked();
    void on_deserializeButton_clicked();
    void on_CustomButton_clicked();
};
#endif // DRAWINGWINDOW_H
