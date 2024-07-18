#ifndef ADDCUSTOMERVIEW_H
#define ADDCUSTOMERVIEW_H

#include <QMainWindow>
#include <QTableWidget>

#include <Services/databaseservice.h>

#include <Entities/manager.h>
#include <Entities/author.h>
#include <Entities/work.h>

namespace Ui {
class AddCustomerView;
}

class AddCustomerView : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddCustomerView(DatabaseService *dbService, Manager *manager, QWidget *parent = nullptr);
    ~AddCustomerView();

private slots:
    void on_pushButton_clicked();

private:
    Ui::AddCustomerView *ui;

    DatabaseService *dbService;
    Manager *wrkManager;
};

#endif // ADDCUSTOMERVIEW_H
