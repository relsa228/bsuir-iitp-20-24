#include "transferdialog.h"
#include "ui_transferdialog.h"
#include <QMessageBox>

//Сервисы
CustomerService* transferCS = new CustomerService();
//Переменные
Customer* transferUser;

TransferDialog::TransferDialog(Customer* customer, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TransferDialog)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/LoginImage/resource/images/mLkk-6k5vpA.png"));
    setWindowTitle("Imperial banking system");

    transferUser = customer;

    ui->SumEdit->setMinimum(1);
    ui->SumEdit->setMaximum(100000000);
    ui->UserEdit->setMaximum(100000000);
    ui->TargetEdit->setMaximum(100000000);

}

void TransferDialog::TransferErrorMessage(QString str)
{
    QMessageBox msg = QMessageBox();
    msg.setWindowIcon(QIcon(":/LoginImage/resource/images/mLkk-6k5vpA.png"));
    msg.setWindowTitle("Ошибка ввода");
    msg.setIcon(msg.Critical);
    msg.setText(str);
    msg.addButton("Принято", msg.AcceptRole);
    msg.exec();
}

void TransferDialog::TransferInformMessage(QString str)
{
    QMessageBox msg = QMessageBox();
    msg.setWindowIcon(QIcon(":/LoginImage/resource/images/mLkk-6k5vpA.png"));
    msg.setWindowTitle("Успѣхъ");
    msg.setIcon(msg.Information);
    msg.setText(str);
    msg.addButton("Принято", msg.AcceptRole);
    msg.exec();
}

TransferDialog::~TransferDialog()
{
    delete ui;
}


void TransferDialog::on_buttonBox_accepted()
{
    bool check = false;
    int index = 0;
    for(int i = 0; i < transferUser->ListOfAccounts->count(); i++)
        if(ui->UserEdit->value() == transferUser->ListOfAccounts->at(i)->getAccId())
        {
            check = true;
            index = i;
        }

    if (check)
    {
        if (ui->SumEdit->value() > transferUser->ListOfAccounts->at(index)->getMoney())
            TransferErrorMessage("Не хватаетъ средствъ");
        else
        {
            if(!transferCS->TransferOperation(ui->SumEdit->value(), ui->TargetEdit->value(), ui->UserEdit->value(), transferUser->getEmail()))
                TransferErrorMessage("Не найденъ цѣлевой счетъ");
            else
                TransferInformMessage("Трансферъ проведенъ успѣшно");
        }
    }
    else
        TransferErrorMessage("У васъ нѣтъ правъ на распоряженіе этимъ счетомъ");

    CustWindow* custwindow = new CustWindow(transferUser);
    custwindow->show();
    this->close();
}


void TransferDialog::on_buttonBox_rejected()
{
    CustWindow* custWindow = new CustWindow(transferUser);
    custWindow->show();
    this->close();
}

