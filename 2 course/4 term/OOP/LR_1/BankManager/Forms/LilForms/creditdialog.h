#ifndef CREDITDIALOG_H
#define CREDITDIALOG_H

#include <QDialog>
#include "Roles/customer.h"
#include "Forms/custwindow.h"

namespace Ui {
class CreditDialog;
}

class CreditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreditDialog(Customer* customer, QWidget *parent = nullptr);
    ~CreditDialog();

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

    void on_BankComboBox_currentTextChanged(const QString &arg1);

private:
    Ui::CreditDialog *ui;
    void CreditErrorMessage(QString str);
    void CreditInformMessage(QString str);
};

#endif // CREDITDIALOG_H
