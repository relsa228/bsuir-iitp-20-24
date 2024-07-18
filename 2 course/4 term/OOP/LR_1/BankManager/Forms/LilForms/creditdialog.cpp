#include "creditdialog.h"
#include "ui_creditdialog.h"
#include <QMessageBox>

//Сервисы
DataBaseService* creditDialogDB = new DataBaseService();
CustomerService* creditDialogCS = new CustomerService();
//Переменные
Customer* creditCustomer;

CreditDialog::CreditDialog(Customer* customer, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreditDialog)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/LoginImage/resource/images/mLkk-6k5vpA.png"));
    setWindowTitle("Imperial banking system");

    creditCustomer = customer;
    QList<Bank*>* banks = creditDialogDB->GetBanks();
    QStringList bankList;

    for(int i = 0; i < banks->count(); i++)
        bankList.push_back(banks->at(i)->getName());

    ui->BankComboBox->addItems(bankList);
    ui->AccName->setMinimum(0);
    ui->AccName->setMaximum(100000000);
    ui->SumOfCredit->setMinimum(1);
    ui->SumOfCredit->setMaximum(100000000);
}

void CreditDialog::CreditErrorMessage(QString str)
{
    QMessageBox msg = QMessageBox();
    msg.setWindowIcon(QIcon(":/LoginImage/resource/images/mLkk-6k5vpA.png"));
    msg.setWindowTitle("Ошибка ввода");
    msg.setIcon(msg.Critical);
    msg.setText(str);
    msg.addButton("Принято", msg.AcceptRole);
    msg.exec();
}

void CreditDialog::CreditInformMessage(QString str)
{
    QMessageBox msg = QMessageBox();
    msg.setWindowIcon(QIcon(":/LoginImage/resource/images/mLkk-6k5vpA.png"));
    msg.setWindowTitle("Успѣхъ");
    msg.setIcon(msg.Information);
    msg.setText(str);
    msg.addButton("Принято", msg.AcceptRole);
    msg.exec();
}

CreditDialog::~CreditDialog()
{
    delete ui;
}


void CreditDialog::on_buttonBox_rejected()
{
    CustWindow* custWindow = new CustWindow(creditCustomer);
    custWindow->show();
    this->close();
}


void CreditDialog::on_buttonBox_accepted()
{
    QList<CreditCircs*>* circs = creditDialogDB->GetCreditCircs();
    bool check = false;

    for(int i = 0; i < creditCustomer->ListOfAccounts->count(); i++)
        if(creditCustomer->ListOfAccounts->at(i)->getAccId() == ui->AccName->value())
            check = true;

    if(check)
    {
        QList<CreditCircs*>* currentCircs = new QList<CreditCircs*>;

        for(int i = 0; i < circs->count(); i++)
            if(circs->at(i)->getBankName() == ui->BankComboBox->currentText())
                currentCircs->push_back(circs->at(i));

        CreditCircs* currentCirc = currentCircs->at(ui->CreditPlan->currentIndex());
        if(creditDialogCS->CheckoutCredit(creditCustomer, ui->AccName->value(), ui->BankComboBox->currentText(), ui->SumOfCredit->value(), currentCirc))
            CreditInformMessage("Заявка отправлена");
        else
            CreditErrorMessage("Банкъ не имѣетъ столько средствъ");
    }
    else
        CreditErrorMessage("Невѣрный номер счета");

    CustWindow* custwindow = new CustWindow(creditCustomer);
    custwindow->show();
    this->close();
}


void CreditDialog::on_BankComboBox_currentTextChanged(const QString &arg1)
{
    ui->CreditPlan->clear();

    QList<CreditCircs*>* circs = creditDialogDB->GetCreditCircs();
    QStringList circsList;
    QString bankName = ui->BankComboBox->currentText();

    for(int i = 0; i < circs->count(); i++)
            if(circs->at(i)->getBankName() == bankName)
            {
                QString toComboBox = "Мѣсяцевъ: ";
                toComboBox.append(QString::number(circs->at(i)->getTerms()));
                toComboBox.append("\nПодъ процентъ: ");
                toComboBox.append(QString::number(circs->at(i)->getProc()));
                circsList.push_back(toComboBox);
            }

    ui->CreditPlan->addItems(circsList);
}

