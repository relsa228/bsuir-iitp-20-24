#include "loginform.h"
#include <QMessageBox>
#include "ui_loginform.h"

//Сервисы
DataBaseService* loginDB = new DataBaseService();

LogInForm::LogInForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LogInForm)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/LoginImage/resource/images/mLkk-6k5vpA.png"));
    setWindowTitle("Imperial banking system");

    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}

void LogInForm::LoginErrorMessage(QString str)
{
    QMessageBox msg = QMessageBox();
    msg.setWindowIcon(QIcon(":/LoginImage/resource/images/Coat_of_arms_of_Russia_Empire_without_shield.png"));
    msg.setWindowTitle("Ошибка ввода");
    msg.setIcon(msg.Critical);
    msg.setText(str);
    msg.addButton("Принято", msg.AcceptRole);
    msg.exec();
}

void LogInForm::LoginInformMessage(QString str)
{
    QMessageBox msg = QMessageBox();
    msg.setWindowIcon(QIcon(":/LoginImage/resource/images/mLkk-6k5vpA.png"));
    msg.setWindowTitle("Входъ выполненъ");
    msg.setIcon(msg.Information);
    msg.setText(str);
    msg.addButton("Принято", msg.AcceptRole);
    msg.exec();
}

LogInForm::~LogInForm()
{
    delete ui;
}

bool LogInForm::CheckOnSpace(QString str)
{
    if(str.isEmpty())
        return false;

    foreach(QString i, str)
        if(i != " ")
            return true;

    return false;
}


void LogInForm::on_Registration_clicked()
{
    RegistrationForm* registrationForm = new RegistrationForm();
    registrationForm->show();
    this->close();
}


void LogInForm::on_Email_textEdited(const QString &arg1)
{
    if (CheckOnSpace(ui->Email->text()) && CheckOnSpace(ui->Password->text()))
        ui->Entry->setEnabled(true);
    else
        ui->Entry->setEnabled(false);
}


void LogInForm::on_Password_textEdited(const QString &arg1)
{
    if (CheckOnSpace(ui->Email->text()) && CheckOnSpace(ui->Password->text()))
        ui->Entry->setEnabled(true);
    else
        ui->Entry->setEnabled(false);
}


void LogInForm::on_Entry_clicked()
{
    User* user = loginDB->Login(ui->Email->text(), ui->Password->text());

    if(user->getPassportSeries() == '0')
        LoginErrorMessage("Ваша записка не подтверждена.");
    else if (user->getPassportSeries() == "-1")
        LoginErrorMessage("Ваша записка закрыта бояриномъ.");
    else if (user->getEmail() == "")
        LoginErrorMessage("Невѣрный почтовый ящикъ или шифръ.");
    else
    {
        QString welcome = "Добро пожаловать, ";
        welcome.append(user->getName());
        welcome.append(" ");
        welcome.append(user->getSurname());
        welcome.append("!");

        LoginInformMessage(welcome);

        if (user->getRoleId() == '4')
        {
            Customer* customer = new Customer;
            customer->setName(user->getName());
            customer->setSurname(user->getSurname());
            customer->setEmail(user->getEmail());
            customer->setTelephone(user->getTelephone());
            customer->setPassportNum(user->getPassportNum());
            customer->setPassportSeries(user->getPassportSeries());
            customer->setRoleId(user->getRoleId());
            customer->setCompanyName(user->getCompanyName());

            CustWindow* custWindow = new CustWindow(customer);
            custWindow->show();
            this->close();
        }
        if (user->getRoleId() == '3')
        {
            EnterpriseSpecialist* enterpriseSpecialist = new EnterpriseSpecialist();
            enterpriseSpecialist->setName(user->getName());
            enterpriseSpecialist->setSurname(user->getSurname());
            enterpriseSpecialist->setEmail(user->getEmail());
            enterpriseSpecialist->setTelephone(user->getTelephone());
            enterpriseSpecialist->setPassportNum(user->getPassportNum());
            enterpriseSpecialist->setPassportSeries(user->getPassportSeries());
            enterpriseSpecialist->setRoleId(user->getRoleId());
            enterpriseSpecialist->setCompanyName(user->getCompanyName());

            SpecWindow* specWindow = new SpecWindow(enterpriseSpecialist);
            specWindow->show();
            this->close();
        }
        if (user->getRoleId() == '2')
        {
            Operator* oper = new Operator();
            oper->setName(user->getName());
            oper->setSurname(user->getSurname());
            oper->setEmail(user->getEmail());
            oper->setTelephone(user->getTelephone());
            oper->setPassportNum(user->getPassportNum());
            oper->setPassportSeries(user->getPassportSeries());
            oper->setRoleId(user->getRoleId());
            oper->setCompanyName(user->getCompanyName());

            OperatorWindow* operWind = new OperatorWindow(oper);
            operWind->show();
            this->close();
        }
        if (user->getRoleId() == '1')
        {
            Manager* manager = new Manager();
            manager->setName(user->getName());
            manager->setSurname(user->getSurname());
            manager->setEmail(user->getEmail());
            manager->setTelephone(user->getTelephone());
            manager->setPassportNum(user->getPassportNum());
            manager->setPassportSeries(user->getPassportSeries());
            manager->setRoleId(user->getRoleId());
            manager->setCompanyName(user->getCompanyName());

            ManagerWindow* managerWind = new ManagerWindow(manager);
            managerWind->show();
            this->close();
        }
        if (user->getRoleId() == '0')
        {
            Administrator* administrator = new Administrator();
            administrator->setName(user->getName());
            administrator->setSurname(user->getSurname());
            administrator->setEmail(user->getEmail());
            administrator->setTelephone(user->getTelephone());
            administrator->setPassportNum(user->getPassportNum());
            administrator->setPassportSeries(user->getPassportSeries());
            administrator->setRoleId(user->getRoleId());
            administrator->setCompanyName(user->getCompanyName());

            AdminWindow* adminWind = new AdminWindow(administrator);
            adminWind->show();
            this->close();
        }
    }
}

