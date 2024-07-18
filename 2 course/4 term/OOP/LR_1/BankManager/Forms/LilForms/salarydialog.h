#ifndef SALARYDIALOG_H
#define SALARYDIALOG_H

#include <QDialog>
#include "Forms/custwindow.h"
#include "Srvices/databaseservice.h"
#include "Entities/bank.h"
#include "Roles/customer.h"

namespace Ui {
class SalaryDialog;
}

class SalaryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SalaryDialog(Customer* customer, QWidget *parent = nullptr);
    ~SalaryDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::SalaryDialog *ui;
    void SalaryInformMessage(QString str);
};

#endif // SALARYDIALOG_H
