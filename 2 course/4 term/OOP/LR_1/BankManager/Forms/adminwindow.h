#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include "Roles/administrator.h"
#include "Srvices/databaseservice.h"
#include "Srvices/administratorservice.h"
#include "Forms/loginform.h"

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminWindow(Administrator* administrator, QWidget *parent = nullptr);
    ~AdminWindow();

private slots:
    void on_TransferCancle_clicked();

    void on_CreditCancle_clicked();

    void on_SalaryCancle_clicked();

    void on_Exit_clicked();

    void on_RejectUser_clicked();

    void on_OpenUser_clicked();

private:
    Ui::AdminWindow *ui;
    void UpdateSalaryTable();
    void UpdateTransferTable();
    void UpdateCreditTable();
    void UpdateUserTable();
    void AdminErrorMsg(QString str);
    void AdminInformMsg(QString str);
};

#endif // ADMINWINDOW_H
