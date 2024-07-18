#ifndef SPECWINDOW_H
#define SPECWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "Entities/bankaccount.h"
#include "Roles/enterprisespecialist.h"
#include "Srvices/databaseservice.h"
#include "Srvices/enterpricespecialistservice.h"
#include "Forms/loginform.h"
#include "Forms/LilForms/companytransferdialog.h"

namespace Ui {
class SpecWindow;
}

class SpecWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SpecWindow(EnterpriseSpecialist* enterpriseSpetialist, QWidget *parent = nullptr);
    ~SpecWindow();

private slots:

    void on_AproveSalary_clicked();

    void on_Exit_clicked();

    void on_AddTransfer_clicked();

private:
    Ui::SpecWindow *ui;
    void SpecErrorMessage(QString str);
    void SpecInformMessage(QString str);
    void UpdateSalaryTable();
    void UpdateAccTable();
};

#endif // SPECWINDOW_H
