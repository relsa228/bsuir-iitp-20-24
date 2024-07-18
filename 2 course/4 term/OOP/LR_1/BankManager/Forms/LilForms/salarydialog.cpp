#include "salarydialog.h"
#include "ui_salarydialog.h"

//Сервисы
CustomerService* salaryCS = new CustomerService();
DataBaseService* salaryDB = new DataBaseService();
//Переменные
Customer* salaryCustomer;

SalaryDialog::SalaryDialog(Customer* customer, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SalaryDialog)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/LoginImage/resource/images/mLkk-6k5vpA.png"));
    setWindowTitle("Imperial banking system");

    salaryCustomer = customer;
    QList<Bank*>* banks = salaryDB->GetBanks();
    QStringList bankList;

    for(int i = 0; i < banks->count(); i++)
        bankList.push_back(banks->at(i)->getName());

    ui->BankComboBox->addItems(bankList);
}

void SalaryDialog::SalaryInformMessage(QString str)
{
    QMessageBox msg = QMessageBox();
    msg.setWindowIcon(QIcon(":/LoginImage/resource/images/mLkk-6k5vpA.png"));
    msg.setWindowTitle("Успѣхъ");
    msg.setIcon(msg.Information);
    msg.setText(str);
    msg.addButton("Принято", msg.AcceptRole);
    msg.exec();
}

SalaryDialog::~SalaryDialog()
{
    delete ui;
}

void SalaryDialog::on_buttonBox_accepted()
{
    salaryCS->CreateSalaryProject(salaryCustomer->getEmail(), ui->BankComboBox->currentText(), salaryCustomer->getCompanyName());
    SalaryInformMessage("Заявка отправлена");
    CustWindow* custwindow = new CustWindow(salaryCustomer);
    custwindow->show();
    this->close();
}


void SalaryDialog::on_buttonBox_rejected()
{
    CustWindow* custwindow = new CustWindow(salaryCustomer);
    custwindow->show();
    this->close();
}

