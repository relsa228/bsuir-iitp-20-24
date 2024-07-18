#ifndef ADMINVIEW_H
#define ADMINVIEW_H

#include <QMainWindow>
#include <QTimer>

#include <Services/databaseservice.h>

#include <Entities/manager.h>
#include <Entities/author.h>
#include <Entities/work.h>
#include <Entities/position.h>

#include <Views/HelpView/addauthor.h>
#include <Views/HelpView/addcustomerview.h>
#include <Views/HelpView/orderview.h>
#include <Views/HelpView/changepasswordview.h>
#include <Views/HelpView/addwork.h>
#include <Views/loginview.h>
#include <Views/HelpView/addmanager.h>

namespace Ui {
class AdminView;
}

class AdminView : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminView(DatabaseService *dbService, Manager *manager, QWidget *parent = nullptr);
    ~AdminView();

private slots:
    void on_pushButton_clicked();
    void updateManagerTable();
    void updateLoggsTable();
    virtual void resizeEvent(QResizeEvent *);

    void on_block_manager_clicked();

    void on_unblock_manager_clicked();

    void on_change_password_clicked();

    void on_add_new_clicked();

private:
    Ui::AdminView *ui;

    DatabaseService *dbService;
    Manager *wrkManager;

    QList<Manager*> *managers;
    QList<Position*> *positions;

    QTimer *timer;
};

#endif // ADMINVIEW_H
