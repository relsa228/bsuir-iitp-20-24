#include "custwindow.h"
#include "ui_custwindow.h"
#include <QMessageBox>

//Сервисы
DataBaseService* custDB = new DataBaseService();
CustomerService* custCS = new CustomerService();
//Переменные
Customer* workCustomer;

CustWindow::CustWindow(Customer* customer, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CustWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/LoginImage/resource/images/mLkk-6k5vpA.png"));
    setWindowTitle("Imperial banking system");

    workCustomer = customer;
    ui->NameLine->setText(customer->getName());
    ui->SurnameLine->setText(customer->getSurname());
    ui->DelSpin->setMaximum(100000000);;

    UpdateAccTable();
    UpdateCreditTable();
}

void CustWindow::UpdateAccTable()
{
    workCustomer->ListOfAccounts = custDB->GetBankAccounts(workCustomer->getEmail());

    ui->AccTable->setColumnCount(4);
    ui->AccTable->setRowCount(workCustomer->ListOfAccounts->count());
    ui->AccTable->setHorizontalHeaderLabels(QStringList() << "Название счета" << "Банк" << "Номер счета" << "Баланс");

    int balance = 0;
    for(int row = 0; row < workCustomer->ListOfAccounts->count(); row++)
    {
        QTableWidgetItem *accName = new QTableWidgetItem(tr("%1").arg(workCustomer->ListOfAccounts->at(row)->getAccName()));
        ui->AccTable->setItem(row, 0, accName);
        ui->AccTable->item(row, 0)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *bank = new QTableWidgetItem(tr("%1").arg(workCustomer->ListOfAccounts->at(row)->getBankName()));
        ui->AccTable->setItem(row, 1, bank);
        ui->AccTable->item(row, 1)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *num = new QTableWidgetItem(tr("%1").arg(workCustomer->ListOfAccounts->at(row)->getAccId()));
        ui->AccTable->setItem(row, 2, num);
        ui->AccTable->item(row, 2)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *money = new QTableWidgetItem(tr("%1").arg(workCustomer->ListOfAccounts->at(row)->getMoney()));
        ui->AccTable->setItem(row, 3, money);
        ui->AccTable->item(row, 3)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        balance += workCustomer->ListOfAccounts->at(row)->getMoney();
    }

    ui->BalanceEdit->setText(QString::number(balance));
}

void CustWindow::UpdateCreditTable()
{
    workCustomer->ListOfCredit = custDB->GetCredits(workCustomer->getEmail());

    ui->CreditTable->setColumnCount(6);
    ui->CreditTable->setRowCount(workCustomer->ListOfCredit->count());
    ui->CreditTable->setHorizontalHeaderLabels(QStringList()<< "Банк" << "Сумма заема" << "Целевой счет" << "Процент" << "Срок" << "Статус");

    for(int row = 0; row < workCustomer->ListOfCredit->count(); row++)
    {
        QTableWidgetItem *bank = new QTableWidgetItem(tr("%1").arg(workCustomer->ListOfCredit->at(row)->getBankName()));
        ui->CreditTable->setItem(row, 0, bank);
        ui->CreditTable->item(row, 0)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *sum = new QTableWidgetItem(tr("%1").arg(QString::number(workCustomer->ListOfCredit->at(row)->getSum())));
        ui->CreditTable->setItem(row, 1, sum);
        ui->CreditTable->item(row, 1)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *acc = new QTableWidgetItem(tr("%1").arg(QString::number(workCustomer->ListOfCredit->at(row)->getAccIndex())));
        ui->CreditTable->setItem(row, 2, acc);
        ui->CreditTable->item(row, 1)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *proc = new QTableWidgetItem(tr("%1").arg(QString::number(workCustomer->ListOfCredit->at(row)->getProcent())));
        ui->CreditTable->setItem(row, 3, proc);
        ui->CreditTable->item(row, 1)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *term = new QTableWidgetItem(tr("%1").arg(QString::number(workCustomer->ListOfCredit->at(row)->getTerm())));
        ui->CreditTable->setItem(row, 4, term);
        ui->CreditTable->item(row, 1)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *stat = new QTableWidgetItem(tr("%1").arg(workCustomer->ListOfCredit->at(row)->getAproveStatus()));
        ui->CreditTable->setItem(row, 5, stat);
        ui->CreditTable->item(row, 1)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);
    }
}

void CustWindow::CustErrorMessage(QString str)
{
    QMessageBox msg = QMessageBox();
    msg.setWindowIcon(QIcon(":/LoginImage/resource/images/mLkk-6k5vpA.png"));
    msg.setWindowTitle("Ошибка ввода");
    msg.setIcon(msg.Critical);
    msg.setText(str);
    msg.addButton("Принято", msg.AcceptRole);
    msg.exec();
}

CustWindow::~CustWindow()
{
    delete ui;
}

void CustWindow::on_OpenAcc_clicked()
{
    AddAcc* addAcc = new AddAcc(workCustomer);
    addAcc->open();
    this->close();
}

void CustWindow::on_CloseAcc_clicked()
{
    int AccId = ui->DelSpin->value();
    bool checkAcc = false, checkCredit = true;

    for(int i = 0; i < workCustomer->ListOfAccounts->count(); i++)
        if(workCustomer->ListOfAccounts->at(i)->getAccId() == AccId)
            checkAcc = true;

    for(int i = 0; i < workCustomer->ListOfCredit->count(); i++)
        if(workCustomer->ListOfCredit->at(i)->getAccIndex() == AccId)
            checkCredit = false;

    if(checkAcc && checkCredit)
    {
        custCS->CloseBankAccount(workCustomer->getEmail(), AccId);
        UpdateAccTable();
    }
    else
    {
        if(!checkAcc)
            CustErrorMessage("Невѣрный номер счета.");
        else
            CustErrorMessage("Вы не можете закрыть счетъ, на который открыта кредитная заявка");
    }
}

void CustWindow::on_Exit_clicked()
{
    LogInForm* login = new LogInForm();
    login->show();
    this->close();
}

void CustWindow::on_AddCredit_clicked()
{
    CreditDialog* credit = new CreditDialog(workCustomer);
    credit->show();
    this->close();
}

void CustWindow::on_Transfer_clicked()
{
    TransferDialog* transferDialog = new TransferDialog(workCustomer);
    transferDialog->show();
    this->close();
}

void CustWindow::on_AddSum_clicked()
{
    InOutDialog* inOutDialog = new InOutDialog(1, workCustomer);
    inOutDialog->show();
    this->close();
}

void CustWindow::on_CashOut_clicked()
{
    InOutDialog* inOutDialog = new InOutDialog(0, workCustomer);
    inOutDialog->show();
    this->close();
}

void CustWindow::on_Request_clicked()
{
    SalaryDialog* salaryDialog = new SalaryDialog(workCustomer);
    salaryDialog->show();
    this->close();
}

