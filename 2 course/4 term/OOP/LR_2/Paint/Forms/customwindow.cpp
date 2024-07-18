#include "customwindow.h"
#include "ui_customwindow.h"

PaintScene* workingScene;

CustomWindow::CustomWindow(PaintScene* paintScene, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CustomWindow)
{
    workingScene = paintScene;

    ui->setupUi(this);
    if(!workingScene->namesOfPlugins->isEmpty())
        ui->selectSpinBox->setMaximum(workingScene->namesOfPlugins->count());
    else
        ui->selectSpinBox->setMaximum(1);
    ui->selectSpinBox->setMinimum(1);

    UpdateCustomFigureTable();
}

CustomWindow::~CustomWindow()
{
    delete ui;
}

void CustomWindow::UpdateCustomFigureTable()
{
    ui->CustomTable->setColumnCount(2);

    for (int i = 0; i < 2; i++)
        ui->CustomTable->setColumnWidth(i, 172);

    ui->CustomTable->setRowCount(workingScene->namesOfPlugins->count());
    ui->CustomTable->setHorizontalHeaderLabels(QStringList()<< "Название фигуры" << "Статус");

    for(int row = 0; row < workingScene->namesOfPlugins->count(); row++)
    {
        QTableWidgetItem *index = new QTableWidgetItem(tr("%1").arg( workingScene->namesOfPlugins->at(row)));
        ui->CustomTable->setItem(row, 0, index);
        ui->CustomTable->item(row, 0)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *BIK = new QTableWidgetItem(tr("%1").arg("Активна"));
        ui->CustomTable->setItem(row, 1, BIK);
        ui->CustomTable->item(row, 1)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);
    }
}

void CustomWindow::on_AcceptButton_clicked()
{
    if(!workingScene->namesOfPlugins->isEmpty())
    {
        int choose = ui->selectSpinBox->value();
        workingScene->setCurrentFigure(workingScene->namesOfPlugins->at(choose - 1));
    }
    this->close();
}

