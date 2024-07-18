#ifndef CUSTWINDOW_H
#define CUSTWINDOW_H

#include <QMainWindow>
#include <Roles/customer.h>
#include "Srvices/databaseservice.h"
#include "Forms/LilForms/addacc.h"
#include "Forms/loginform.h"
#include "Forms/LilForms/creditdialog.h"
#include "Forms/LilForms/transferdialog.h"
#include "Forms/LilForms/inoutdialog.h"
#include "Forms/LilForms/salarydialog.h"

namespace Ui {
class CustWindow;
}

class CustWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CustWindow(Customer* customer, QWidget *parent = nullptr);
    ~CustWindow();

private slots:
    void on_OpenAcc_clicked();

    void on_CloseAcc_clicked();

    void on_Exit_clicked();

    void on_AddCredit_clicked();

    void on_Transfer_clicked();

    void on_AddSum_clicked();

    void on_CashOut_clicked();

    void on_Request_clicked();

private:
    Ui::CustWindow *ui;
    void UpdateAccTable();
    void UpdateCreditTable();
    void CustErrorMessage(QString str);
};

#endif // CUSTWINDOW_H
