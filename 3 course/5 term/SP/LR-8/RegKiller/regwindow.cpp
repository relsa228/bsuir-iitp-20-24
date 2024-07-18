#include "regwindow.h"
#include "ui_regwindow.h"

RegWindow::RegWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RegWindow)
{
    ui->setupUi(this);

    regWorkerService = new RegWorkerService();
    tableService = new TableService(ui->outTable);
    option = HKEY_CLASSES_ROOT;
}

RegWindow::~RegWindow()
{
    delete ui;
}

void RegWindow::resizeEvent(QResizeEvent *)
{
    float newSize = ui->outTable->size().width()/3;
    if (newSize > 33) {
        if(ui->outTable->rowCount() == 0)
            for (int i = 0; i < 3; i++)
                ui->outTable->setColumnWidth(i, newSize);
        else
            for (int i = 0; i < 3; i++)
                ui->outTable->setColumnWidth(i, newSize - 6.5);
    }
}

void RegWindow::on_searchButton_clicked()
{
    ui->outTable->clearContents();
    ui->outTable->setRowCount(0);

    QString address = ui->addrEdit->text();
    QString bufAddress = QString("%1").arg(address);
    std::wstring inptAddress = bufAddress.toStdWString();

    QString name = ui->nameEdit->text();
    QString bufName = QString("%1").arg(name);
    std::wstring inptName = bufName.toStdWString();

    if (!name.isEmpty()) {
        RegUnit regUnit = regWorkerService->extractUnit(inptAddress.c_str(), inptName.c_str(), REG_SZ, option);
        if (regUnit.getUnitType() != "")
            tableService->AddUnitToTable(regUnit);
        return;
    }

    QVector<RegUnit> *regUnits = regWorkerService->extractUnits(inptAddress.c_str(), REG_SZ, option);
    tableService->AddUnitsToTable(regUnits);
}

void RegWindow::on_settingsButton_clicked()
{
    SettingsWindow *settingsWindow = new SettingsWindow(&option);
    settingsWindow->show();
}


void RegWindow::on_exportButton_clicked()
{
    QVector<RegUnit> *regUnits;
    QString address = ui->addrEdit->text();
    QString bufAddress = QString("%1").arg(address);
    std::wstring inptAddress = bufAddress.toStdWString();

    QString name = ui->nameEdit->text();
    QString bufName = QString("%1").arg(name);
    std::wstring inptName = bufName.toStdWString();

    if (!name.isEmpty()) {
        regUnits = new QVector<RegUnit>();
        regUnits->push_back(regWorkerService->extractUnit(inptAddress.c_str(), inptName.c_str(), REG_SZ, option));
    }
    else
        regUnits = regWorkerService->extractUnits(inptAddress.c_str(), REG_SZ, option);

    QString filePath = QFileDialog::getSaveFileName(
                            this,
                            tr("Сохранить файл"),
                            "",
                            tr("Файлы реестра (*.reg)" )
                            );

    regWorkerService->exportSettings(regUnits, address, option, filePath);
}

