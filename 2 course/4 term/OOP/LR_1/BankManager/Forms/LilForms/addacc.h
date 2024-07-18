#ifndef ADDACC_H
#define ADDACC_H

#include <QDialog>
#include "Roles/customer.h"
#include "Srvices/customerservice.h"
#include "Forms/custwindow.h"

namespace Ui {
class AddAcc;
}

class AddAcc : public QDialog
{
    Q_OBJECT

public:
    explicit AddAcc(Customer* customer, QWidget *parent = nullptr);
    ~AddAcc();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::AddAcc *ui;
};

#endif // ADDACC_H
