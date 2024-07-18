#include "companytransferdialog.h"
#include "ui_companytransferdialog.h"

//Сервисы
DataBaseService* compTransferDB = new DataBaseService();
EnterpriceSpecialistService* compTransferES = new EnterpriceSpecialistService();
//Переменные
EnterpriseSpecialist* transferSpec;
QList<BankAccount*>* listOfAccounts;

CompanyTransferDialog::CompanyTransferDialog(EnterpriseSpecialist* enterpriseSpetialist, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CompanyTransferDialog)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/LoginImage/resource/images/mLkk-6k5vpA.png"));
    setWindowTitle("Imperial banking system");

    transferSpec = enterpriseSpetialist;
    listOfAccounts = compTransferDB->GetBankAccounts(enterpriseSpetialist->getCompanyName());

    QStringList nameList;
    for(int i = 0; i < listOfAccounts->count(); i++)
        nameList.push_back(listOfAccounts->at(i)->getAccName());

    ui->AccBox->addItems(nameList);
    ui->SumEdit->setMaximum(100000000);
}

void CompanyTransferDialog::CompanyTransferErrorMessage(QString str)
{
    QMessageBox msg = QMessageBox();
    msg.setWindowIcon(QIcon(":/LoginImage/resource/images/mLkk-6k5vpA.png"));
    msg.setWindowTitle("Ошибка ввода");
    msg.setIcon(msg.Critical);
    msg.setText(str);
    msg.addButton("Принято", msg.AcceptRole);
    msg.exec();
}

void CompanyTransferDialog::CompanyTransferInformMessage(QString str)
{
    QMessageBox msg = QMessageBox();
    msg.setWindowIcon(QIcon(":/LoginImage/resource/images/mLkk-6k5vpA.png"));
    msg.setWindowTitle("Успѣхъ");
    msg.setIcon(msg.Information);
    msg.setText(str);
    msg.addButton("Принято", msg.AcceptRole);
    msg.exec();
}

CompanyTransferDialog::~CompanyTransferDialog()
{
    delete ui;
}

void CompanyTransferDialog::on_buttonBox_accepted()
{
    QString currentAcc = ui->AccBox->currentText();
    int accIndex = 0;
    int currentSum = 0;

    for(int i = 0; i < listOfAccounts->count(); i++)
        if (currentAcc == listOfAccounts->at(i)->getAccName())
        {
            accIndex = listOfAccounts->at(i)->getAccId();
            currentSum = listOfAccounts->at(i)->getMoney();
        }

    if(currentSum < ui->SumEdit->value())
        CompanyTransferErrorMessage("На счетѣ не хватаетъ средствъ");

    if(compTransferES->CorporateTransfer(accIndex, ui->TargetEdit->value(), ui->SumEdit->value(), transferSpec->getEmail()))
        CompanyTransferInformMessage("Заявка на переводъ принята");
    else
        CompanyTransferErrorMessage("Во время проведенія операціи произошла ошибка. Провѣрьте ​введенные​ ​данные​.");

    SpecWindow* specWindow = new SpecWindow(transferSpec);
    specWindow->show();
    this->close();
}


void CompanyTransferDialog::on_buttonBox_rejected()
{
    SpecWindow* specWindow = new SpecWindow(transferSpec);
    specWindow->show();
    this->close();
}

