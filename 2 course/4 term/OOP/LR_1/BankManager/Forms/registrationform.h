#ifndef REGISTRATIONFORM_H
#define REGISTRATIONFORM_H

#include <QMainWindow>
#include "Forms/loginform.h"
#include "Roles/customer.h"
#include "Srvices/databaseservice.h"

namespace Ui {
class RegistrationForm;
}

class LogInForm;
class Customer;
class DataBaseService;

class RegistrationForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegistrationForm(QWidget *parent = nullptr);
    ~RegistrationForm();

private slots:
    void on_Submit_clicked();

    void on_Cancle_clicked();

    void on_Name_textEdited(const QString &arg1);

    void on_Surname_textEdited(const QString &arg1);

    void on_Telephone_textEdited(const QString &arg1);

    void on_Email_textEdited(const QString &arg1);

    void on_PasportSer_textEdited(const QString &arg1);

    void on_PasportNum_textEdited(const QString &arg1);

    void on_Password_textEdited(const QString &arg1);

    void on_ConfirmPassword_textEdited(const QString &arg1);

    void on_international_clicked();

private:
    Ui::RegistrationForm *ui;

    void RegistrationErrorMessage(QString str);
    void RegistrationInformMessage(QString str);
    void CheckInput();
    bool CheckOnSpace(QString str);
};

#endif // REGISTRATIONFORM_H
