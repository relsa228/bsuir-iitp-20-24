#include "managerwindow.h"
#include "ui_managerwindow.h"

//Сервисы
ManagerService* managerMS = new ManagerService();
DataBaseService* managerDB = new DataBaseService();
//Переменная
Manager* workManager;

ManagerWindow::ManagerWindow(Manager* manager, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ManagerWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/LoginImage/resource/images/mLkk-6k5vpA.png"));
    setWindowTitle("Imperial banking system");

    workManager = manager;
    UpdateCreditTable();
    UpdateSalaryTable();
    UpdateTransferTable();
    UpdateUserTable();
}

void ManagerWindow::UpdateCreditTable()
{
    workManager->creditList = managerDB->GetCredits("manager");

    ui->CreditTable->setColumnCount(7);

    for (int i = 0; i < 7; i++)
        ui->CreditTable->setColumnWidth(i, 115);

    ui->CreditTable->setRowCount(workManager->creditList->count());
    ui->CreditTable->setHorizontalHeaderLabels(QStringList()<< "Номер заявки" << "Банк" << "Запросил" << "Целевой счет" << "Сумма" << "Процент" << "Срок (мес.)");

    for(int row = 0; row < workManager->creditList->count(); row++)
    {
        QTableWidgetItem *index = new QTableWidgetItem(tr("%1").arg(workManager->creditList->at(row)->getCreditId()));
        ui->CreditTable->setItem(row, 0, index);
        ui->CreditTable->item(row, 0)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *bank = new QTableWidgetItem(tr("%1").arg(workManager->creditList->at(row)->getBankName()));
        ui->CreditTable->setItem(row, 1, bank);
        ui->CreditTable->item(row, 1)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *user = new QTableWidgetItem(tr("%1").arg(workManager->creditList->at(row)->getUserName()));
        ui->CreditTable->setItem(row, 2, user);
        ui->CreditTable->item(row, 2)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *acc = new QTableWidgetItem(tr("%1").arg(workManager->creditList->at(row)->getAccIndex()));
        ui->CreditTable->setItem(row, 3, acc);
        ui->CreditTable->item(row, 3)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *sum = new QTableWidgetItem(tr("%1").arg(workManager->creditList->at(row)->getSum()));
        ui->CreditTable->setItem(row, 4, sum);
        ui->CreditTable->item(row, 4)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *procent = new QTableWidgetItem(tr("%1").arg(workManager->creditList->at(row)->getProcent()));
        ui->CreditTable->setItem(row, 5, procent);
        ui->CreditTable->item(row, 5)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *term = new QTableWidgetItem(tr("%1").arg(workManager->creditList->at(row)->getTerm()));
        ui->CreditTable->setItem(row, 6, term);
        ui->CreditTable->item(row, 6)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);
    }

}

void ManagerWindow::UpdateSalaryTable()
{
    workManager->salaryList = managerDB->GetSalaryProjects("manager");

    ui->SalaryTable->setColumnCount(6);

    for (int i = 0; i < 6; i++)
        ui->SalaryTable->setColumnWidth(i, 135);

    ui->SalaryTable->setRowCount(workManager->salaryList->count());
    ui->SalaryTable->setHorizontalHeaderLabels(QStringList()<< "Индекс проекта" << "Компания" << "БИК банка" << "Предложил" << "Подал документы" << "Статус");

    for(int row = 0; row < workManager->salaryList->count(); row++)
    {
        QTableWidgetItem *index = new QTableWidgetItem(tr("%1").arg(workManager->salaryList->at(row)->getIndex()));
        ui->SalaryTable->setItem(row, 0, index);
        ui->SalaryTable->item(row, 0)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *companyName = new QTableWidgetItem(tr("%1").arg(workManager->salaryList->at(row)->getCompanyName()));
        ui->SalaryTable->setItem(row, 1, companyName);
        ui->SalaryTable->item(row, 1)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *BIK = new QTableWidgetItem(tr("%1").arg(workManager->salaryList->at(row)->getBIK()));
        ui->SalaryTable->setItem(row, 2, BIK);
        ui->SalaryTable->item(row, 2)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *userName = new QTableWidgetItem(tr("%1").arg(workManager->salaryList->at(row)->getUsername()));
        ui->SalaryTable->setItem(row, 3, userName);
        ui->SalaryTable->item(row, 3)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *specName = new QTableWidgetItem(tr("%1").arg(workManager->salaryList->at(row)->getSpecialist()));
        ui->SalaryTable->setItem(row, 4, specName);
        ui->SalaryTable->item(row, 4)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *status = new QTableWidgetItem(tr("%1").arg(workManager->salaryList->at(row)->getApproveStatus()));
        ui->SalaryTable->setItem(row, 5, status);
        ui->SalaryTable->item(row, 5)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);
    }
}

void ManagerWindow::UpdateTransferTable()
{
    workManager->userTransfers = managerDB->GetTransfers("manager");

    ui->TransferTable->setColumnCount(5);

    for (int i = 0; i < 5; i++)
        ui->TransferTable->setColumnWidth(i, 165);

    ui->TransferTable->setRowCount(workManager->userTransfers->count());
    ui->TransferTable->setHorizontalHeaderLabels(QStringList()<< "Номер трансфера" << "Инициатор" << "Счет отправителя" << "Счет получателя" << "Сумма");

    for(int row = 0; row < workManager->userTransfers->count(); row++)
    {
        QTableWidgetItem *index = new QTableWidgetItem(tr("%1").arg(workManager->userTransfers->at(row)->getTransferId()));
        ui->TransferTable->setItem(row, 0, index);
        ui->TransferTable->item(row, 0)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *init = new QTableWidgetItem(tr("%1").arg(workManager->userTransfers->at(row)->getInit()));
        ui->TransferTable->setItem(row, 1, init);
        ui->TransferTable->item(row, 1)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *sender = new QTableWidgetItem(tr("%1").arg(workManager->userTransfers->at(row)->getSenderId()));
        ui->TransferTable->setItem(row, 2, sender);
        ui->TransferTable->item(row, 2)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *target = new QTableWidgetItem(tr("%1").arg(workManager->userTransfers->at(row)->getTargetId()));
        ui->TransferTable->setItem(row, 3, target);
        ui->TransferTable->item(row, 3)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *sum = new QTableWidgetItem(tr("%1").arg(workManager->userTransfers->at(row)->getSum()));
        ui->TransferTable->setItem(row, 4, sum);
        ui->TransferTable->item(row, 4)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);
    }
}

void ManagerWindow::UpdateUserTable()
{
    workManager->userList = managerDB->GetUsers("manager");

    ui->UserTable->setColumnCount(8);

    for (int i = 0; i < 8; i++)
        ui->UserTable->setColumnWidth(i, 100);

    ui->UserTable->setRowCount(workManager->userList->count());
    ui->UserTable->setHorizontalHeaderLabels(QStringList()<< "Индекс" << "Имя" << "Фамилия" << "Телефон" << "Почта" << "Компания" << "Номер паспорта" << "Серия паспорта");

    for(int row = 0; row < workManager->userList->count(); row++)
    {
        QTableWidgetItem *index = new QTableWidgetItem(tr("%1").arg(workManager->userList->at(row)->getUserId()));
        ui->UserTable->setItem(row, 0, index);
        ui->UserTable->item(row, 0)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *name = new QTableWidgetItem(tr("%1").arg(workManager->userList->at(row)->getName()));
        ui->UserTable->setItem(row, 1, name);
        ui->UserTable->item(row, 1)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *surname = new QTableWidgetItem(tr("%1").arg(workManager->userList->at(row)->getSurname()));
        ui->UserTable->setItem(row, 2, surname);
        ui->UserTable->item(row, 2)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *telephone = new QTableWidgetItem(tr("%1").arg(workManager->userList->at(row)->getTelephone()));
        ui->UserTable->setItem(row, 3, telephone);
        ui->UserTable->item(row, 3)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *email = new QTableWidgetItem(tr("%1").arg(workManager->userList->at(row)->getEmail()));
        ui->UserTable->setItem(row, 4, email);
        ui->UserTable->item(row, 4)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *company = new QTableWidgetItem(tr("%1").arg(workManager->userList->at(row)->getCompanyName()));
        ui->UserTable->setItem(row, 5, company);
        ui->UserTable->item(row, 5)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *passNum = new QTableWidgetItem(tr("%1").arg(workManager->userList->at(row)->getPassportNum()));
        ui->UserTable->setItem(row, 6, passNum);
        ui->UserTable->item(row, 6)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *passSer = new QTableWidgetItem(tr("%1").arg(workManager->userList->at(row)->getPassportSeries()));
        ui->UserTable->setItem(row, 7, passSer);
        ui->UserTable->item(row, 7)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);
    }
}

void ManagerWindow::ManagerErrorMessage(QString str)
{
    QMessageBox msg = QMessageBox();
    msg.setWindowIcon(QIcon(":/LoginImage/resource/images/mLkk-6k5vpA.png"));
    msg.setWindowTitle("Ошибка ввода");
    msg.setIcon(msg.Critical);
    msg.setText(str);
    msg.addButton("Принято", msg.AcceptRole);
    msg.exec();
}

void ManagerWindow::ManagerInformMessage(QString str)
{
    QMessageBox msg = QMessageBox();
    msg.setWindowIcon(QIcon(":/LoginImage/resource/images/mLkk-6k5vpA.png"));
    msg.setWindowTitle("Успѣхъ");
    msg.setIcon(msg.Information);
    msg.setText(str);
    msg.addButton("Принято", msg.AcceptRole);
    msg.exec();
}

ManagerWindow::~ManagerWindow()
{
    delete ui;
}

void ManagerWindow::on_AproveCredit_clicked()
{
    int index = ui->CreditBox->value();
    Credit* currentCredit = new Credit();
    currentCredit->setAccIndex(-1);

    for(int i = 0; i < workManager->creditList->count(); i++)
        if(workManager->creditList->at(i)->getCreditId() == index)
            currentCredit = workManager->creditList->at(i);

    if(currentCredit->getAccIndex() != -1)
    {
        if(managerMS->AproveCredit(currentCredit, workManager->getEmail()))
            ManagerInformMessage("Заявка одобрена");
        else
            ManagerErrorMessage("Въ банкѣ недостаточно средствъ");
    }
    else
        ManagerErrorMessage("Невѣрный индексъ кредитной заявки");

    UpdateCreditTable();
}

void ManagerWindow::on_AproveSalary_clicked()
{
    int index = ui->SalaryBox->value();
    bool check = false;

    for(int i = 0; i < workManager->salaryList->count(); i++)
        if(workManager->salaryList->at(i)->getIndex() == index)
            check = true;

    if(check)
    {
        managerMS->ApproveSalaryProject(index, workManager->getEmail());
        UpdateSalaryTable();
        ManagerInformMessage("Зарплатный​ проектъ утвержденъ");
    }
    else
        ManagerErrorMessage("Невѣрный индексъ зарплатного проекта");

    UpdateSalaryTable();
}

void ManagerWindow::on_RejectTransfer_clicked()
{
    Transfer* transfer = new Transfer();

    transfer->setTransferId(-1);
    for(int i = 0; i < workManager->userTransfers->count(); i++)
        if(workManager->userTransfers->at(i)->getTransferId() == ui->TransferBox->value())
            transfer = workManager->userTransfers->at(i);

    if(transfer->getTransferId() != -1 && transfer->getAprove() != "Waiting")
    {
        managerMS->CancelCustomerTransfer(transfer, workManager->getEmail());
        UpdateTransferTable();
        ManagerInformMessage("Дѣйствіе по счету отмѣнено");
    }
    else if (transfer->getTransferId() != -1 && transfer->getAprove() == "Waiting")
    {
        managerMS->CancleCorpTransfer(transfer->getTransferId());
        ManagerInformMessage("Дѣйствіе по счету предпріятія отмѣнено.");
    }
    else
        ManagerErrorMessage("Невѣрный индексъ перевода");

    UpdateTransferTable();
}

void ManagerWindow::on_AproveUser_clicked()
{
    bool check = false;
    for(int i = 0; i < workManager->userList->count(); i++)
        if(workManager->userList->at(i)->getUserId() == ui->UserBox->value())
            check = true;

    if(check)
    {
        managerMS->AproveCustomer(ui->UserBox->value(), workManager->getEmail());
        ManagerInformMessage("Записка кліента открыта");
    }
    else
        ManagerErrorMessage("Невѣрный индексъ кліента");

    UpdateUserTable();
}

void ManagerWindow::on_Exit_clicked()
{
    LogInForm* login = new LogInForm();
    login->show();
    this->close();
}


