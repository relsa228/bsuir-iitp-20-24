#ifndef THICKNESSFORM_H
#define THICKNESSFORM_H

#include <QDialog>

#include "Entities/paintscene.h"

namespace Ui {
class ThicknessForm;
}

class ThicknessForm : public QDialog
{
    Q_OBJECT

public:
    explicit ThicknessForm(PaintScene* paintScene, QWidget *parent = nullptr);
    ~ThicknessForm();

    PaintScene* workScene;
    int thickness;

private slots:
    void on_BigradioButton_clicked();
    void on_MidradioButton_2_clicked();
    void on_SmallradioButton_3_clicked();
    void on_ThiccBox_valueChanged(int arg1);
    void on_AcceptButton_clicked();
    void on_CancleButton_clicked();

private:
    Ui::ThicknessForm *ui;
};

#endif // THICKNESSFORM_H
