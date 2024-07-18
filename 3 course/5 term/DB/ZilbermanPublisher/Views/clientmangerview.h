#ifndef CLIENTMANGERVIEW_H
#define CLIENTMANGERVIEW_H

#include <QMainWindow>
#include <QTimer>

#include <Services/databaseservice.h>

#include <Entities/manager.h>
#include <Entities/author.h>
#include <Entities/work.h>

#include <Views/HelpView/addauthor.h>
#include <Views/HelpView/addcustomerview.h>
#include <Views/HelpView/orderview.h>
#include <Views/HelpView/addwork.h>
#include <Views/loginview.h>

namespace Ui {
class ClientMangerView;
}

class ClientMangerView : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClientMangerView(DatabaseService *dbService, Manager *manager, QWidget *parent = nullptr);
    ~ClientMangerView();

private slots:
    void on_add_author_clicked();

    void on_add_customer_clicked();

    void on_add_order_clicked();

    void on_add_work_clicked();
    void updateAuthorTab();
    void updateOrderTab();
    void updateWorkTab();
    void updateCustomerTab();

    virtual void resizeEvent(QResizeEvent *);

    void on_exit_clicked();

    void on_close_clicked();

private:
    Ui::ClientMangerView *ui;

    DatabaseService *dbService;
    Manager *wrkManager;

    QTimer *timer;
};

#endif // CLIENTMANGERVIEW_H
