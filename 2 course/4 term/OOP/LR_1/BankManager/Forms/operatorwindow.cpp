#include "operatorwindow.h"
#include "ui_operatorwindow.h"

//Сервисы
DataBaseService* operatorDB = new DataBaseService();
OperatorService* operatorOS = new OperatorService();
//Переменные
Operator* workOper;

OperatorWindow::OperatorWindow(Operator* oper, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OperatorWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/LoginImage/resource/images/mLkk-6k5vpA.png"));
    setWindowTitle("Imperial banking system");

    ui->AproveBox->setMaximum(100000000);
    ui->DeclineBox->setMaximum(100000000);
    workOper = oper;
    UpdateSalaryTable();
    UpdateTransferTable();
}

void OperatorWindow::UpdateTransferTable()
{ 
    workOper->userTransfers = operatorDB->GetTransfers("user");

    ui->TransferTable->setColumnCount(5);

    for (int i = 0; i < 5; i++)
        ui->TransferTable->setColumnWidth(i, 180);

    ui->TransferTable->setRowCount(workOper->userTransfers->count());
    ui->TransferTable->setHorizontalHeaderLabels(QStringList()<< "Номер трансфера" << "Инициатор" << "Счет отправителя" << "Счет получателя" << "Сумма");

    for(int row = 0; row < workOper->userTransfers->count(); row++)
    {
        QTableWidgetItem *index = new QTableWidgetItem(tr("%1").arg(workOper->userTransfers->at(row)->getTransferId()));
        ui->TransferTable->setItem(row, 0, index);
        ui->TransferTable->item(row, 0)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *companyName = new QTableWidgetItem(tr("%1").arg(workOper->userTransfers->at(row)->getInit()));
        ui->TransferTable->setItem(row, 1, companyName);
        ui->TransferTable->item(row, 1)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *BIK = new QTableWidgetItem(tr("%1").arg(workOper->userTransfers->at(row)->getSenderId()));
        ui->TransferTable->setItem(row, 2, BIK);
        ui->TransferTable->item(row, 2)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *userName = new QTableWidgetItem(tr("%1").arg(workOper->userTransfers->at(row)->getTargetId()));
        ui->TransferTable->setItem(row, 3, userName);
        ui->TransferTable->item(row, 3)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *specName = new QTableWidgetItem(tr("%1").arg(workOper->userTransfers->at(row)->getSum()));
        ui->TransferTable->setItem(row, 4, specName);
        ui->TransferTable->item(row, 4)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);
    }
}

void OperatorWindow::UpdateSalaryTable()
{
    workOper->salaryList = operatorDB->GetSalaryProjects("manager");

    ui->SalaryTable->setColumnCount(6);

    for (int i = 0; i < 6; i++)
        ui->SalaryTable->setColumnWidth(i, 150);

    ui->SalaryTable->setRowCount(workOper->salaryList->count());
    ui->SalaryTable->setHorizontalHeaderLabels(QStringList()<< "Индекс проекта" << "Компания" << "БИК банка" << "Предложил" << "Подал документы" << "Статус");

    for(int row = 0; row < workOper->salaryList->count(); row++)
    {
        QTableWidgetItem *index = new QTableWidgetItem(tr("%1").arg(workOper->salaryList->at(row)->getIndex()));
        ui->SalaryTable->setItem(row, 0, index);
        ui->SalaryTable->item(row, 0)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *companyName = new QTableWidgetItem(tr("%1").arg(workOper->salaryList->at(row)->getCompanyName()));
        ui->SalaryTable->setItem(row, 1, companyName);
        ui->SalaryTable->item(row, 1)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *BIK = new QTableWidgetItem(tr("%1").arg(workOper->salaryList->at(row)->getBIK()));
        ui->SalaryTable->setItem(row, 2, BIK);
        ui->SalaryTable->item(row, 2)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *userName = new QTableWidgetItem(tr("%1").arg(workOper->salaryList->at(row)->getUsername()));
        ui->SalaryTable->setItem(row, 3, userName);
        ui->SalaryTable->item(row, 3)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *specName = new QTableWidgetItem(tr("%1").arg(workOper->salaryList->at(row)->getSpecialist()));
        ui->SalaryTable->setItem(row, 4, specName);
        ui->SalaryTable->item(row, 4)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *status = new QTableWidgetItem(tr("%1").arg(workOper->salaryList->at(row)->getApproveStatus()));
        ui->SalaryTable->setItem(row, 5, status);
        ui->SalaryTable->item(row, 5)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);
    }
}

void OperatorWindow::OperatorErrorMessage(QString str)
{
    QMessageBox msg = QMessageBox();
    msg.setWindowIcon(QIcon(":/LoginImage/resource/images/mLkk-6k5vpA.png"));
    msg.setWindowTitle("Ошибка ввода");
    msg.setIcon(msg.Critical);
    msg.setText(str);
    msg.addButton("Принято", msg.AcceptRole);
    msg.exec();
}

void OperatorWindow::OperatorInformMessage(QString str)
{
    QMessageBox msg = QMessageBox();
    msg.setWindowIcon(QIcon(":/LoginImage/resource/images/mLkk-6k5vpA.png"));
    msg.setWindowTitle("Успѣхъ");
    msg.setIcon(msg.Information);
    msg.setText(str);
    msg.addButton("Принято", msg.AcceptRole);
    msg.exec();
}

OperatorWindow::~OperatorWindow()
{
    delete ui;
}

void OperatorWindow::on_Exit_clicked()
{
    LogInForm* login = new LogInForm();
    login->show();
    this->close();
}


void OperatorWindow::on_Aprove_clicked()
{
    int index = ui->AproveBox->value();
    bool check = false;

    for(int i = 0; i < workOper->salaryList->count(); i++)
        if(workOper->salaryList->at(i)->getIndex() == index)
            check = true;

    if(check)
    {
        operatorOS->ApproveSalaryProject(index, workOper->getEmail());
        UpdateSalaryTable();
        OperatorInformMessage("Зарплатный​ проектъ утвержденъ");
    }
    else
        OperatorErrorMessage("Невѣрный индексъ зарплатного проекта");
}


void OperatorWindow::on_Decline_clicked()
{
    Transfer* transfer = new Transfer();
    transfer->setTransferId(-1);
    for(int i = 0; i < workOper->userTransfers->count(); i++)
        if(workOper->userTransfers->at(i)->getTransferId() == ui->DeclineBox->value())
            transfer = workOper->userTransfers->at(i);

    if(transfer->getTransferId() != -1)
    {
        operatorOS->CancelCustomerTransfer(transfer, workOper->getEmail());
        UpdateTransferTable();
        OperatorInformMessage("Дѣйствіе по счету отмѣнено");
    }
    else
        OperatorErrorMessage("Невѣрный индексъ трансфера");
}

