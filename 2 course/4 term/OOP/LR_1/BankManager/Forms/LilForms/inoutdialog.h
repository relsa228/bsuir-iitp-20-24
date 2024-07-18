#ifndef INOUTDIALOG_H
#define INOUTDIALOG_H

#include <QDialog>
#include "Roles/customer.h"
#include "Forms/custwindow.h"
#include "Srvices/customerservice.h"
#include <QMessageBox>

namespace Ui {
class InOutDialog;
}

class InOutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InOutDialog(int operationIndes, Customer* customer, QWidget *parent = nullptr);
    ~InOutDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::InOutDialog *ui;
    void InOutErrorMessage(QString str);
    void InOutInformMessage(QString str);
};

#endif // INOUTDIALOG_H
