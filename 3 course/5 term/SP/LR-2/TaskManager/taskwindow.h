#ifndef TASKWINDOW_H
#define TASKWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QProcess>
#include <QTimer>
#include <QFile>
#include <QPrintDialog>
#include <QPrinter>
#include <QPainter>

#include <Services/tableservice.h>
#include <Services/processservice.h>
#include <Services/Messages/errormsgservice.h>
#include <Services/Messages/infomsgservice.h>
#include <Services/reportservice.h>

QT_BEGIN_NAMESPACE
namespace Ui { class TaskWindow; }
QT_END_NAMESPACE

class TaskWindow : public QMainWindow
{
    Q_OBJECT

public:
    TaskWindow(QWidget *parent = nullptr);
    ~TaskWindow();

private:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_updateTable();

    void on_startProcButton_clicked();

    void on_selectProcButton_clicked();

    void on_restartProcButton_clicked();

    void on_pauseProcButton_clicked();

    void on_terminateProcButton_clicked();

    void on_printReportButton_clicked();

    void on_getReportButton_clicked();

    void on_cleanTableButton_clicked();

private:
    Ui::TaskWindow *ui;

    TableService* tableService;
    ProcessService* processService;
    ReportService* reportService;

    QTimer *timer;
};
#endif // TASKWINDOW_H
