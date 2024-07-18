#include "taskwindow.h"
#include "ui_taskwindow.h"

TaskWindow::TaskWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TaskWindow)
{
    ui->setupUi(this);

    tableService = new TableService(ui->processView);
    processService = new ProcessService();
    reportService = new ReportService();

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(on_updateTable()));
    timer->start(100);
}

TaskWindow::~TaskWindow()
{
    delete ui;
}

void TaskWindow::on_updateTable()
{
    tableService->updateFullTable();
}


void TaskWindow::on_startProcButton_clicked()
{
    QString exePath = ui->fileName->text();

    if(exePath.isEmpty()) {
        ErrorMsgService("Сначала выберите исполняемый файл");
        return;
    }

    foreach (Process* proc, tableService->processCollection) {
        if(proc->getProcRootDir() + proc->getProcName() + ".exe" == exePath &&
                proc->getProcessSign()->state() == QProcess::Running) {
            InfoMsgService("Этот процесс уже запущен");
            return;
        }
    }

    tableService->pushNewProcess(processService->createProcess(exePath));
}


void TaskWindow::on_selectProcButton_clicked()
{
    QString exePath = QFileDialog::getOpenFileName(
                        this,
                        tr("Открыть"),
                        "",
                        tr("EXE (*.exe);;JPEG (*.jpg *.jpeg)" )
                        );
    ui->fileName->setText(exePath);
}


void TaskWindow::on_restartProcButton_clicked()
{
    int index = ui->processView->currentRow();
    if(index == -1) ErrorMsgService("Необходимо выбрать процесс");
    else {
        processService->rerunProcess(tableService->processCollection.at(index));
        tableService->updateProcess(index, tableService->processCollection.at(index));
    }
}


void TaskWindow::on_pauseProcButton_clicked()
{
    int index = ui->processView->currentRow();
    if(index == -1) ErrorMsgService("Необходимо выбрать процесс");
    else {
        processService->closeProcess(tableService->processCollection.at(index));
        tableService->updateProcess(index, tableService->processCollection.at(index));
    }
}


void TaskWindow::on_terminateProcButton_clicked()
{
    int index = ui->processView->currentRow();
    if(index == -1) ErrorMsgService("Необходимо выбрать процесс");
    else {
        processService->terminateProcess(tableService->processCollection.at(index));
        tableService->updateProcess(index, tableService->processCollection.at(index));
    }
}

void TaskWindow::on_cleanTableButton_clicked()
{
    tableService->dropTable();
}

void TaskWindow::closeEvent(QCloseEvent *event)
{
    tableService->dropTable();
}

///////////////////reports//////////////////////////////
void TaskWindow::on_printReportButton_clicked()
{
    QPrinter printer;

    QPrintDialog *dialog = new QPrintDialog(&printer);
    dialog->setWindowTitle("Print Document");

    if (dialog->exec() != QDialog::Accepted)
        return;

    QPainter painter;
    painter.begin(&printer);

    painter.drawText(100, 100, 1500, 1500, Qt::AlignLeft|Qt::AlignTop,
                     reportService->getReport(tableService->processCollection, QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm:ss")));

    painter.end();

    return;
}


void TaskWindow::on_getReportButton_clicked()
{
    QString reportSavePath = QFileDialog::getSaveFileName(this, tr("Сохранить файл"), "",
                                                          tr("TXT (*.txt)"));
    QFile fileOut(reportSavePath);
    if(fileOut.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream writeStream(&fileOut);
        writeStream << reportService->getReport(tableService->processCollection, QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm:ss"));
        fileOut.close();
    }
}
