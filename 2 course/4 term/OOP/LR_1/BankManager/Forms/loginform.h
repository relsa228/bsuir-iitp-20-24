#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QMainWindow>
#include "Forms/registrationform.h"
#include "Forms/custwindow.h"
#include "Forms/adminwindow.h"
#include "Forms/managerwindow.h"
#include "Forms/operatorwindow.h"
#include "Forms/specwindow.h"
#include "Srvices/databaseservice.h"
#include "Roles/administrator.h"
#include "Roles/customer.h"
#include "Roles/enterprisespecialist.h"
#include "Roles/manager.h"
#include "Roles/operator.h"

class RegistrationForm;
class DataBaseService;
class CustWindow;

namespace Ui {
class LogInForm;
}

class LogInForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit LogInForm(QWidget *parent = nullptr);
    ~LogInForm();

private slots:
    void on_Registration_clicked();

    void on_Email_textEdited(const QString &arg1);

    void on_Password_textEdited(const QString &arg1);

    void on_Entry_clicked();

private:
    Ui::LogInForm *ui;
    bool CheckOnSpace(QString str);
    void LoginErrorMessage(QString str);
    void LoginInformMessage(QString str);
};

#endif // LOGINFORM_H
