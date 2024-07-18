#include "addacc.h"
#include "ui_addacc.h"

//Сервисы
CustomerService* accountCS = new CustomerService();
DataBaseService* accountDB = new DataBaseService();
//Переменные
Customer* addCustomer;

AddAcc::AddAcc(Customer* customer, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddAcc)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/LoginImage/resource/images/mLkk-6k5vpA.png"));
    setWindowTitle("Imperial banking system");

    addCustomer = customer;
    QList<Bank*>* banks = accountDB->GetBanks();
    QStringList bankList;

    for(int i = 0; i < banks->count(); i++)
        bankList.push_back(banks->at(i)->getName());

    ui->BankComboBox->addItems(bankList);
}

AddAcc::~AddAcc()
{
    delete ui;
}

void AddAcc::on_buttonBox_accepted()
{
    accountCS->OpenBankAccount(addCustomer, ui->BankComboBox->currentText(), ui->AccName->text());
    CustWindow* custWindow = new CustWindow(addCustomer);
    custWindow->show();
    this->close();
}


void AddAcc::on_buttonBox_rejected()
{
    CustWindow* custWindow = new CustWindow(addCustomer);
    custWindow->show();
    this->close();
}

