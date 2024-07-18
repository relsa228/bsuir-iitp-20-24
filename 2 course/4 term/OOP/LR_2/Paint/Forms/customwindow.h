#ifndef CUSTOMWINDOW_H
#define CUSTOMWINDOW_H

#include <QMainWindow>

#include "Entities/paintscene.h"

namespace Ui {
class CustomWindow;
}

class CustomWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CustomWindow(PaintScene* paintScene, QWidget *parent = nullptr);
    ~CustomWindow();

private slots:
    void on_AcceptButton_clicked();

private:
    Ui::CustomWindow *ui;
    void UpdateCustomFigureTable();
};

#endif // CUSTOMWINDOW_H
