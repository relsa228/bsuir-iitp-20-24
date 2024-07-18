#ifndef PRINTCENTERMANAGERVIEW_H
#define PRINTCENTERMANAGERVIEW_H

#include <QMainWindow>
#include <QTimer>

#include "Entities/manager.h"
#include "Services/databaseservice.h"
#include <Views/loginview.h>

namespace Ui {
class PrintCenterManagerView;
}

class PrintCenterManagerView : public QMainWindow
{
    Q_OBJECT

public:
    explicit PrintCenterManagerView(DatabaseService *dbService, Manager *manager, QWidget *parent = nullptr);
    ~PrintCenterManagerView();

private slots:
    void on_start_work_clicked();

    void updateOnWorkTable();
    void updateReadyTable();

    void on_deny_work_clicked();

    void on_exit_clicked();

    virtual void resizeEvent(QResizeEvent *);
private:
    Ui::PrintCenterManagerView *ui;

    PrintCenter* printCenter;
    DatabaseService *dbService;
    Manager *wrkManager;

    QList<Batch*> *onWorkBatches;
    QList<Batch*> *readyBatches;

    QTimer *timer;
};

#endif // PRINTCENTERMANAGERVIEW_H
