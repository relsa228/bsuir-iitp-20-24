#ifndef TRANSFERDIALOG_H
#define TRANSFERDIALOG_H

#include <QDialog>
#include "Forms/custwindow.h"
#include "Roles/customer.h"
#include "Entities/transfer.h"
#include "Srvices/databaseservice.h"

namespace Ui {
class TransferDialog;
}

class Transfer;

class TransferDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TransferDialog(Customer* customer, QWidget *parent = nullptr);
    ~TransferDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::TransferDialog *ui;
    void TransferErrorMessage(QString str);
    void TransferInformMessage(QString str);
};

#endif // TRANSFERDIALOG_H
