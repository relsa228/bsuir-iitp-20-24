#ifndef REGWINDOW_H
#define REGWINDOW_H

#include <windows.h>
#include <QMainWindow>
#include <QFileDialog>

#include <settingswindow.h>

#include <Entities/regunit.h>

#include <Services/regworkerservice.h>
#include <Services/tableservice.h>

QT_BEGIN_NAMESPACE
namespace Ui { class RegWindow; }
QT_END_NAMESPACE

class RegWindow : public QMainWindow
{
    Q_OBJECT

public:
    RegWindow(QWidget *parent = nullptr);
    ~RegWindow();

private slots:
    void on_searchButton_clicked();

    virtual void resizeEvent(QResizeEvent *);

    void on_settingsButton_clicked();

    void on_exportButton_clicked();

private:
    Ui::RegWindow *ui;
    RegWorkerService *regWorkerService;
    TableService *tableService;
    HKEY option;

    void regRead(LPCTSTR subkey, LPCTSTR name, DWORD type);
};
#endif // REGWINDOW_H
