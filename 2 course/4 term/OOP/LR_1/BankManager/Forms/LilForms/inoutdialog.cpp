#include "inoutdialog.h"
#include "ui_inoutdialog.h"

//Сервисы
CustomerService* inOutCS = new CustomerService();
//Переменные
Customer* inOutCustomer;
int currentOperationIndex;

InOutDialog::InOutDialog(int operationIndex, Customer* customer, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InOutDialog)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/LoginImage/resource/images/mLkk-6k5vpA.png"));
    setWindowTitle("Imperial banking system");

    currentOperationIndex = operationIndex;
    inOutCustomer = customer;
    ui->SumEdit->setMinimum(1);
    ui->SumEdit->setMaximum(100000000);
    ui->TargetEdit->setMaximum(100000000);
}

void InOutDialog::InOutErrorMessage(QString str)
{
    QMessageBox msg = QMessageBox();
    msg.setWindowIcon(QIcon(":/LoginImage/resource/images/mLkk-6k5vpA.png"));
    msg.setWindowTitle("Ошибка ввода");
    msg.setIcon(msg.Critical);
    msg.setText(str);
    msg.addButton("Принято", msg.AcceptRole);
    msg.exec();
}

void InOutDialog::InOutInformMessage(QString str)
{
    QMessageBox msg = QMessageBox();
    msg.setWindowIcon(QIcon(":/LoginImage/resource/images/mLkk-6k5vpA.png"));
    msg.setWindowTitle("Успѣхъ");
    msg.setIcon(msg.Information);
    msg.setText(str);
    msg.addButton("Принято", msg.AcceptRole);
    msg.exec();
}

InOutDialog::~InOutDialog()
{
    delete ui;
}

void InOutDialog::on_buttonBox_accepted()
{
    bool check = false;
    int index = 0;
    for(int i = 0; i < inOutCustomer->ListOfAccounts->count(); i++)
        if(ui->TargetEdit->value() == inOutCustomer->ListOfAccounts->at(i)->getAccId())
        {
            check = true;
            index = i;
        }

    if (check)
    {
        if (ui->SumEdit->value() > inOutCustomer->ListOfAccounts->at(index)->getMoney() && currentOperationIndex == 0)
            InOutErrorMessage("Не хватаетъ средствъ");
        else
        {
            inOutCS->CashInOut(ui->TargetEdit->value(), ui->SumEdit->value(), currentOperationIndex);
            InOutInformMessage("Переводъ проведенъ успѣшно");
        }
    }
    else
        InOutErrorMessage("У васъ нѣтъ правъ на распоряженіе этимъ счетомъ");

    CustWindow* custwindow = new CustWindow(inOutCustomer);
    custwindow->show();
    this->close();
}


void InOutDialog::on_buttonBox_rejected()
{
    CustWindow* custwindow = new CustWindow(inOutCustomer);
    custwindow->show();
    this->close();
}

