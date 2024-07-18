#include "Forms/drawingwindow.h"
#include "ui_drawingwindow.h"

QString ellipse = typeid (new DefaultEllipse()).name();
QString rectangle = typeid (new DefaultRectangle()).name();
QString line = typeid (new DefaultLine()).name();
QString path = typeid (new DefaultPath()).name();
QString plot = typeid (new DefaultPlot()).name();

DrawingWindow::DrawingWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DrawingWindow)
{
    colorDialog = new QColorDialog();
    colorDialog->setWindowIcon(QIcon(":/newLogo/Logo/Logo-1.png"));
    colorDialog->update();

    ui->setupUi(this);
    ui->RotateSlider->setMaximum(370);
    color = Qt::black;
    colorBrush = Qt::white;
    currentRotate = 0;

    paintScene = new PaintScene();
    paintScene->setCurrentPenColor(color);
    paintScene->setCurrentBrushColor(colorBrush);
    paintScene->setCurrentThickness(10);
    ui->graphicsView->setScene(paintScene);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &DrawingWindow::slotTimer);
    timer->start(100);
}

DrawingWindow::~DrawingWindow()
{
    delete ui;
}


void DrawingWindow::ErrorMsg(QString str)
{
    QMessageBox msg = QMessageBox();
    msg.setWindowIcon(QIcon(":/new/Logo/Logo/Logo-80.png"));
    msg.setWindowTitle("Ошибка");
    msg.setIcon(msg.Critical);
    msg.setText(str);
    msg.addButton("Принято", msg.AcceptRole);
    msg.exec();
}


void DrawingWindow::slotTimer()
{
    timer->stop();
    paintScene->setSceneRect(0,0, ui->graphicsView->width() - 20, ui->graphicsView->height() - 20);
}


void DrawingWindow::resizeEvent(QResizeEvent *event)
{
    timer->start(100);
    QWidget::resizeEvent(event);
}


void DrawingWindow::on_FillButton_clicked()
{
    this->paintScene->setTargetTool(3);
    colorBrush = colorDialog->getColor(colorBrush, colorDialog, "PicMan");
    if (colorBrush.isValid())
    {
        QString hexRgb = QString("#%1").arg(QColor(colorBrush).rgba(), 8, 16);
        QString hexInput = "border-radius: 1px; background-color: ";
        hexInput.append(hexRgb);
        paintScene->setCurrentBrushColor(colorBrush);
    }
}


void DrawingWindow::on_EraserButton_clicked()
{
    this->paintScene->setTargetTool(2);
}


void DrawingWindow::on_BrushButton_clicked()
{
    this->paintScene->setTargetTool(1);
}


void DrawingWindow::on_moveButton_clicked()
{
    this->paintScene->setTargetTool(0);
}


void DrawingWindow::on_ThicknessButton_clicked()
{
    ThicknessForm* thicknessForm = new ThicknessForm(this->paintScene);
    thicknessForm->show();
}


void DrawingWindow::on_ColorButton_clicked()
{
    color = colorDialog->getColor(color, colorDialog, "PicMan");
    if (color.isValid())
    {
        QString hexRgb = QString("#%1").arg(QColor(color).rgba(), 8, 16);
        QString hexInput = "border-radius: 1px; background-color: ";
        hexInput.append(hexRgb);
        ui->ColorButton->setStyleSheet(hexInput);
        paintScene->setCurrentPenColor(color);
    }
}


void DrawingWindow::on_SaveButton_clicked()
{
    QString imagePath = QFileDialog::getSaveFileName(
                        this,
                        tr("Сохранить файл"),
                        "",
                        tr("PNG (*.png);;JPEG (*.jpg *.jpeg)" )
                        );
    QImage image;
    image = ui->graphicsView->grab().toImage();
    image.save(imagePath);
}


void DrawingWindow::on_UploadButton_clicked()
{
    QString imagePath = QFileDialog::getOpenFileName(
                        this,
                        tr("Загрузить файл"),
                        "",
                        tr("PNG (*.png);;JPEG (*.jpg *.jpeg)" )
                        );
    QImage *image = new QImage();
    image->load(imagePath);

    QPixmap loadImg = QPixmap::fromImage(*image);
    paintScene->addPixmap(loadImg);
    paintScene->setSceneRect(loadImg.rect());
    ui->graphicsView->setScene(paintScene);
}


void DrawingWindow::on_CircleButton_clicked()
{
    paintScene->setCurrentFigure(ellipse);
}


void DrawingWindow::on_RectangleButton_clicked()
{
    paintScene->setCurrentFigure(rectangle);
}


void DrawingWindow::on_LineButton_clicked()
{
    paintScene->setCurrentFigure(line);
}


void DrawingWindow::on_CurveButton_clicked()
{
    paintScene->setCurrentFigure(path);
}


void DrawingWindow::on_HexagonButton_clicked()
{
    paintScene->setCurrentFigure(plot);
}


void DrawingWindow::on_RotateRightButton_clicked()
{
    paintScene->rotate(10);
}


void DrawingWindow::on_RotateLeftButton_clicked()
{
     paintScene->rotate(-10);
}


void DrawingWindow::on_RotateSlider_sliderMoved(int position)
{
    paintScene->rotate(position - currentRotate);
    currentRotate = ui->RotateSlider->value();
}


void DrawingWindow::on_zoomButton_clicked()
{
    paintScene->zoom(0.1);
}


void DrawingWindow::on_unzoomButton_clicked()
{
    paintScene->zoom(-0.1);
}


void DrawingWindow::on_UndoButton_clicked()
{
    paintScene->undo();
}


void DrawingWindow::on_RedoButton_clicked()
{
    paintScene->redo();
}

void DrawingWindow::on_delButton_clicked()
{
    paintScene->deleteItem();
}


void DrawingWindow::on_copyButton_clicked()
{
    paintScene->setTargetTool(5);
}


void DrawingWindow::on_serializeButton_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(
                        this,
                        tr("Сохранить файл"),
                        "defName",
                        tr("JSON (*.json)" )
                        );
    paintScene->dump(filePath);
}


void DrawingWindow::on_deserializeButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(
                        this,
                        tr("Загрузить файл"),
                        "",
                        tr("JSON (*.json)" )
                        );
    paintScene->load(filePath);
}


void DrawingWindow::on_CustomButton_clicked()
{
    CustomWindow* customWindow = new CustomWindow(this->paintScene);
    customWindow->show();
}

