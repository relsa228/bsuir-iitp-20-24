#ifndef OPERATORWINDOW_H
#define OPERATORWINDOW_H

#include <QMainWindow>
#include "Roles/operator.h"
#include "Forms/loginform.h"
#include "Srvices/operatorservice.h"

namespace Ui {
class OperatorWindow;
}

class OperatorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit OperatorWindow(Operator* oper, QWidget *parent = nullptr);
    ~OperatorWindow();

private slots:
    void on_Exit_clicked();

    void on_Aprove_clicked();

    void on_Decline_clicked();

private:
    Ui::OperatorWindow *ui;
    void UpdateSalaryTable();
    void UpdateTransferTable();
    void OperatorErrorMessage(QString str);
    void OperatorInformMessage(QString str);
};

#endif // OPERATORWINDOW_H
