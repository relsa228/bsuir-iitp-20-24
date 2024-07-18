#include "registrationform.h"
#include "ui_registrationform.h"
#include "Roles/customer.h"
#include <QMessageBox>
#include <QRegularExpression>

//Переменные
bool internationalCheck = false;
//Сервисы
DataBaseService* registrationDB = new DataBaseService();

RegistrationForm::RegistrationForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RegistrationForm)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/LoginImage/resource/images/mLkk-6k5vpA.png"));
    setWindowTitle("Imperial banking system");

    ui->Telephone->setInputMask("8-000-000-0000;");
    ui->PasportNum->setInputMask("0000000;");
    ui->PasportSer->setInputMask("AA;");

    QStringList companyList = registrationDB->GetCompanyName();
    ui->Company->addItems(companyList);
}

void RegistrationForm::RegistrationErrorMessage(QString str)
{
    QMessageBox msg = QMessageBox();
    msg.setWindowIcon(QIcon(":/LoginImage/resource/images/mLkk-6k5vpA.png"));
    msg.setWindowTitle("Ошибка ввода");
    msg.setIcon(msg.Critical);
    msg.setText(str);
    msg.addButton("Принято", msg.AcceptRole);
    msg.exec();
}

void RegistrationForm::RegistrationInformMessage(QString str)
{
    QMessageBox msg = QMessageBox();
    msg.setWindowIcon(QIcon(":/LoginImage/resource/images/mLkk-6k5vpA.png"));
    msg.setWindowTitle("Входъ выполненъ");
    msg.setIcon(msg.Information);
    msg.setText(str);
    msg.addButton("Принято", msg.AcceptRole);
    msg.exec();
}

void RegistrationForm::CheckInput()
{
    if (CheckOnSpace(ui->Email->text()) && CheckOnSpace(ui->Password->text()) && CheckOnSpace(ui->ConfirmPassword->text())
            && CheckOnSpace(ui->Name->text()) && CheckOnSpace(ui->PasportNum->text()) && CheckOnSpace(ui->PasportSer->text())
            && CheckOnSpace(ui->Telephone->text()) && CheckOnSpace(ui->Surname->text()))
        ui->Submit->setEnabled(true);
    else
        ui->Submit->setEnabled(false);
}

bool RegistrationForm::CheckOnSpace(QString str)
{
    if(str.isEmpty())
        return false;

    foreach(QString i, str)
        if(i != " ")
            return true;

    return false;
}

RegistrationForm::~RegistrationForm()
{
    delete ui;
}

void RegistrationForm::on_Submit_clicked()
{
    bool telephoneCheck = false, passwordCheck = false, passportCheck = false, emailCheck = false, emailEnabledCheck = true;

    QRegularExpression emailRX("^[0-9a-zA-Z]+([0-9a-zA-Z]*[-._+])*[0-9a-zA-Z]+@[0-9a-zA-Z]+([-.][0-9a-zA-Z]+)*([0-9a-zA-Z]*[.])[a-zA-Z]{2,6}$");
    QString email = ui->Email->text();
    emailCheck = email.contains(emailRX);

    if(!emailCheck)
        RegistrationErrorMessage("Невѣрный почтовый ящикъ");

    if(ui->Telephone->text().length() != 14)
        RegistrationErrorMessage("Невѣрный вводъ телефона");
    else
        telephoneCheck = true;

    if(ui->ConfirmPassword->text() != ui->Password->text())
        RegistrationErrorMessage("Шифры не совпадаютъ");
    else
        passwordCheck = true;

    if(!internationalCheck)
    {
        if(ui->PasportSer->text().length() != 2 || ui->PasportNum->text().length() != 7)
            RegistrationErrorMessage("Серія или номеръ паспорта невѣрны");
        else
            passportCheck = true;
    }
    else
    {
        QRegularExpression passRX("^[a-zA-Z0-9]+$");
        QRegularExpression nationalRX("^[a-zA-Z]$");

        QString passport = ui->PasportSer->text();

        if(ui->PasportSer->text().isEmpty() || !passport.contains(passRX))
        {
            RegistrationErrorMessage("Номеръ паспорта невѣренъ");
            passportCheck = false;
        }
        else
            passportCheck = true;

        foreach(QString i, ui->PasportNum->text())
        {
            if(i == " " || i == "-" || i.contains(nationalRX)){}
            else
            {
                RegistrationErrorMessage("Подданство невѣрно");
                passportCheck = false;
                break;
            }
        }
    }

    QList<User*>* usernames = registrationDB->GetUsers("admin");
    for(int i = 0; i < usernames->count(); i++)
        if(usernames->at(i)->getEmail() == ui->Email->text())
        {
            emailEnabledCheck = false;
            RegistrationErrorMessage("Пользователь съ такимъ почтовымъ ящикомъ уже ​зарегестрированъ​");
        }

    if(telephoneCheck && passwordCheck && passportCheck && emailEnabledCheck && emailCheck)
    {
        Customer* customer = new Customer();
        customer->setName(ui->Name->text());
        customer->setSurname(ui->Surname->text());
        customer->setEmail(ui->Email->text());
        customer->setTelephone(ui->Telephone->text());
        customer->setCompanyName(ui->Company->currentText());
        customer->setRoleId("4");
        customer->setPassportNum(ui->PasportNum->text());
        customer->setPassportSeries(ui->PasportSer->text());

        registrationDB->AddCustomer(customer, ui->Password->text());

        RegistrationInformMessage("Запись завершена успѣшно");

        LogInForm* logInForm = new LogInForm();
        logInForm->show();
        this->close();
    }
}

void RegistrationForm::on_Cancle_clicked()
{
    LogInForm* logInForm = new LogInForm();
    logInForm->show();
    this->close();
}

void RegistrationForm::on_Name_textEdited(const QString &arg1)
{
    CheckInput();
}

void RegistrationForm::on_Surname_textEdited(const QString &arg1)
{
    CheckInput();
}

void RegistrationForm::on_Telephone_textEdited(const QString &arg1)
{
    CheckInput();
}

void RegistrationForm::on_Email_textEdited(const QString &arg1)
{
    CheckInput();
}

void RegistrationForm::on_PasportSer_textEdited(const QString &arg1)
{
    CheckInput();
}

void RegistrationForm::on_PasportNum_textEdited(const QString &arg1)
{
    CheckInput();
}

void RegistrationForm::on_Password_textEdited(const QString &arg1)
{
    CheckInput();
}

void RegistrationForm::on_ConfirmPassword_textEdited(const QString &arg1)
{
    CheckInput();
}

void RegistrationForm::on_international_clicked()
{
    if(ui->international->checkState())
    {
        ui->PassportSer_lable->setText("Серія и номеръ паспорта");
        ui->PassportNum_lable->setText("Подданство ");
        ui->PasportNum->setInputMask("");
        ui->PasportSer->setInputMask("");
    }
    else
    {
        ui->PassportSer_lable->setText("Серія паспорта");
        ui->PassportNum_lable->setText("Номеръ паспорта");
        ui->PasportNum->setInputMask("0000000;");
        ui->PasportSer->setInputMask("AA;");
    }

    internationalCheck = ui->international->checkState();
}

