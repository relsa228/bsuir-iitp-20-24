#include "thicknessform.h"
#include "ui_thicknessform.h"

ThicknessForm::ThicknessForm(PaintScene* paintScene, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ThicknessForm)
{
    ui->setupUi(this);
    ui->ThiccBox->setMaximum(100);
    ui->ThiccBox->setMinimum(1);

    thickness = paintScene->getCurrentThickness();
    workScene = paintScene;
}

ThicknessForm::~ThicknessForm()
{
    delete ui;
}

void ThicknessForm::on_BigradioButton_clicked()
{
    thickness = 100;
}


void ThicknessForm::on_MidradioButton_2_clicked()
{
    thickness = 50;
}


void ThicknessForm::on_SmallradioButton_3_clicked()
{
    thickness = 1;
}


void ThicknessForm::on_ThiccBox_valueChanged(int arg1)
{
    thickness = ui->ThiccBox->value();
}


void ThicknessForm::on_AcceptButton_clicked()
{
    workScene->setCurrentThickness(thickness);
    this->close();
}


void ThicknessForm::on_CancleButton_clicked()
{
    this->close();
}

