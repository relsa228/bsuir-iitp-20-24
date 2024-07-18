#ifndef COMPANYTRANSFERDIALOG_H
#define COMPANYTRANSFERDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "Roles/enterprisespecialist.h"
#include "Entities/bankaccount.h"
#include "Srvices/databaseservice.h"
#include "Srvices/enterpricespecialistservice.h"
#include "Forms/specwindow.h"

namespace Ui {
class CompanyTransferDialog;
}

class CompanyTransferDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CompanyTransferDialog(EnterpriseSpecialist* enterpriseSpetialist, QWidget *parent = nullptr);
    ~CompanyTransferDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::CompanyTransferDialog *ui;
    void CompanyTransferErrorMessage(QString str);
    void CompanyTransferInformMessage(QString str);
};

#endif // COMPANYTRANSFERDIALOG_H
