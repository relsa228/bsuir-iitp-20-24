#ifndef MANAGERWINDOW_H
#define MANAGERWINDOW_H

#include <QMainWindow>
#include "Roles/manager.h"
#include "Forms/loginform.h"
#include "Srvices/databaseservice.h"
#include "Srvices/managerservice.h"

namespace Ui {
class ManagerWindow;
}

class ManagerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ManagerWindow(Manager* manager, QWidget *parent = nullptr);
    ~ManagerWindow();

private slots:
    void on_AproveCredit_clicked();

    void on_AproveSalary_clicked();

    void on_RejectTransfer_clicked();

    void on_Exit_clicked();

    void on_AproveUser_clicked();

private:
    Ui::ManagerWindow *ui;
    void UpdateSalaryTable();
    void UpdateTransferTable();
    void UpdateCreditTable();
    void UpdateUserTable();
    void ManagerErrorMessage(QString str);
    void ManagerInformMessage(QString str);
};

#endif // MANAGERWINDOW_H
