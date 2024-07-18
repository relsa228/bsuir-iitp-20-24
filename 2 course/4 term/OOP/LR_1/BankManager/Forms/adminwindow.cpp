#include "adminwindow.h"
#include "ui_adminwindow.h"

//Сервисы
AdministratorService* adminAS = new AdministratorService();
DataBaseService* adminDB = new DataBaseService();
//Переменные
Administrator* mainAdmin;
QList<Bank*>* banks;

AdminWindow::AdminWindow(Administrator* administrator, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/LoginImage/resource/images/mLkk-6k5vpA.png"));
    setWindowTitle("Imperial banking system");

    banks = adminDB->GetBanks();
    mainAdmin = administrator;
    UpdateCreditTable();
    UpdateSalaryTable();
    UpdateTransferTable();
    UpdateUserTable();
}

void AdminWindow::UpdateUserTable()
{
    mainAdmin->userList = adminDB->GetUsers("all");

    ui->UserTable->setColumnCount(10);

    for (int i = 0; i < 10; i++)
        ui->UserTable->setColumnWidth(i, 92);

    ui->UserTable->setRowCount(mainAdmin->userList->count());
    ui->UserTable->setHorizontalHeaderLabels(QStringList()<< "Индекс" << "Имя" << "Фамилия" << "Телефон" << "Почта" << "Компания" << "Номер паспорта" << "Серия паспорта" << "Роль" << "Статус аккаунта");

    for(int row = 0; row < mainAdmin->userList->count(); row++)
    {
        QTableWidgetItem *index = new QTableWidgetItem(tr("%1").arg(mainAdmin->userList->at(row)->getUserId()));
        ui->UserTable->setItem(row, 0, index);
        ui->UserTable->item(row, 0)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *name = new QTableWidgetItem(tr("%1").arg(mainAdmin->userList->at(row)->getName()));
        ui->UserTable->setItem(row, 1, name);
        ui->UserTable->item(row, 1)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *surname = new QTableWidgetItem(tr("%1").arg(mainAdmin->userList->at(row)->getSurname()));
        ui->UserTable->setItem(row, 2, surname);
        ui->UserTable->item(row, 2)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *telephone = new QTableWidgetItem(tr("%1").arg(mainAdmin->userList->at(row)->getTelephone()));
        ui->UserTable->setItem(row, 3, telephone);
        ui->UserTable->item(row, 3)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *email = new QTableWidgetItem(tr("%1").arg(mainAdmin->userList->at(row)->getEmail()));
        ui->UserTable->setItem(row, 4, email);
        ui->UserTable->item(row, 4)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *company = new QTableWidgetItem(tr("%1").arg(mainAdmin->userList->at(row)->getCompanyName()));
        ui->UserTable->setItem(row, 5, company);
        ui->UserTable->item(row, 5)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *passNum = new QTableWidgetItem(tr("%1").arg(mainAdmin->userList->at(row)->getPassportNum()));
        ui->UserTable->setItem(row, 6, passNum);
        ui->UserTable->item(row, 6)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *passSer = new QTableWidgetItem(tr("%1").arg(mainAdmin->userList->at(row)->getPassportSeries()));
        ui->UserTable->setItem(row, 7, passSer);
        ui->UserTable->item(row, 7)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *role = new QTableWidgetItem(tr("%1").arg(mainAdmin->userList->at(row)->getRoleId()));
        ui->UserTable->setItem(row, 8, role);
        ui->UserTable->item(row, 8)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *status = new QTableWidgetItem(tr("%1").arg(mainAdmin->userList->at(row)->getAproveStatus()));
        ui->UserTable->setItem(row, 9, status);
        ui->UserTable->item(row, 9)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);
    }
}

void AdminWindow::UpdateCreditTable()
{
    mainAdmin->creditList = adminDB->GetCredits("all");

    ui->CreditTable->setColumnCount(8);

    for (int i = 0; i < 8; i++)
        ui->CreditTable->setColumnWidth(i, 110);

    ui->CreditTable->setRowCount(mainAdmin->creditList->count());
    ui->CreditTable->setHorizontalHeaderLabels(QStringList()<< "Номер заявки" << "Банк" << "Запросил" << "Целевой счет" << "Сумма" << "Процент" << "Срок (мес.)" << "Подтверждение");

    for(int row = 0; row < mainAdmin->creditList->count(); row++)
    {
        QTableWidgetItem *index = new QTableWidgetItem(tr("%1").arg(mainAdmin->creditList->at(row)->getCreditId()));
        ui->CreditTable->setItem(row, 0, index);
        ui->CreditTable->item(row, 0)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *bank = new QTableWidgetItem(tr("%1").arg(mainAdmin->creditList->at(row)->getBankName()));
        ui->CreditTable->setItem(row, 1, bank);
        ui->CreditTable->item(row, 1)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *user = new QTableWidgetItem(tr("%1").arg(mainAdmin->creditList->at(row)->getUserName()));
        ui->CreditTable->setItem(row, 2, user);
        ui->CreditTable->item(row, 2)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *acc = new QTableWidgetItem(tr("%1").arg(mainAdmin->creditList->at(row)->getAccIndex()));
        ui->CreditTable->setItem(row, 3, acc);
        ui->CreditTable->item(row, 3)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *sum = new QTableWidgetItem(tr("%1").arg(mainAdmin->creditList->at(row)->getSum()));
        ui->CreditTable->setItem(row, 4, sum);
        ui->CreditTable->item(row, 4)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *procent = new QTableWidgetItem(tr("%1").arg(mainAdmin->creditList->at(row)->getProcent()));
        ui->CreditTable->setItem(row, 5, procent);
        ui->CreditTable->item(row, 5)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *term = new QTableWidgetItem(tr("%1").arg(mainAdmin->creditList->at(row)->getTerm()));
        ui->CreditTable->setItem(row, 6, term);
        ui->CreditTable->item(row, 6)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *aprove = new QTableWidgetItem(tr("%1").arg(mainAdmin->creditList->at(row)->getAproveStatus()));
        ui->CreditTable->setItem(row, 7, aprove);
        ui->CreditTable->item(row, 7)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);
    }
}

void AdminWindow::UpdateSalaryTable()
{
    mainAdmin->salaryList = adminDB->GetSalaryProjects("all");

    ui->SalaryTable->setColumnCount(8);

    for (int i = 0; i < 8; i++)
        ui->SalaryTable->setColumnWidth(i, 115);

    ui->SalaryTable->setRowCount(mainAdmin->salaryList->count());
    ui->SalaryTable->setHorizontalHeaderLabels(QStringList()<< "Индекс проекта" << "Компания" << "БИК банка" << "БИК пред. банка" << "Предложил" << "Подал документы" << "Утвердил в системе" << "Статус");

    for(int row = 0; row < mainAdmin->salaryList->count(); row++)
    {
        QTableWidgetItem *index = new QTableWidgetItem(tr("%1").arg(mainAdmin->salaryList->at(row)->getIndex()));
        ui->SalaryTable->setItem(row, 0, index);
        ui->SalaryTable->item(row, 0)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *companyName = new QTableWidgetItem(tr("%1").arg(mainAdmin->salaryList->at(row)->getCompanyName()));
        ui->SalaryTable->setItem(row, 1, companyName);
        ui->SalaryTable->item(row, 1)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *BIK = new QTableWidgetItem(tr("%1").arg(mainAdmin->salaryList->at(row)->getBIK()));
        ui->SalaryTable->setItem(row, 2, BIK);
        ui->SalaryTable->item(row, 2)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *prevBIK = new QTableWidgetItem(tr("%1").arg(mainAdmin->salaryList->at(row)->getPrevBIK()));
        ui->SalaryTable->setItem(row, 3, prevBIK);
        ui->SalaryTable->item(row, 3)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *userName = new QTableWidgetItem(tr("%1").arg(mainAdmin->salaryList->at(row)->getUsername()));
        ui->SalaryTable->setItem(row, 4, userName);
        ui->SalaryTable->item(row, 4)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *specName = new QTableWidgetItem(tr("%1").arg(mainAdmin->salaryList->at(row)->getSpecialist()));
        ui->SalaryTable->setItem(row, 5, specName);
        ui->SalaryTable->item(row, 5)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *sysName = new QTableWidgetItem(tr("%1").arg(mainAdmin->salaryList->at(row)->getOperator()));
        ui->SalaryTable->setItem(row, 6, sysName);
        ui->SalaryTable->item(row, 6)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *status = new QTableWidgetItem(tr("%1").arg(mainAdmin->salaryList->at(row)->getApproveStatus()));
        ui->SalaryTable->setItem(row, 7, status);
        ui->SalaryTable->item(row, 7)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);
    }
}

void AdminWindow::UpdateTransferTable()
{
    mainAdmin->transferList = adminDB->GetTransfers("all");

    ui->TransferTable->setColumnCount(6);

    for (int i = 0; i < 6; i++)
        ui->TransferTable->setColumnWidth(i, 150);

    ui->TransferTable->setRowCount(mainAdmin->transferList->count());
    ui->TransferTable->setHorizontalHeaderLabels(QStringList()<< "Номер трансфера" << "Инициатор" << "Счет отправителя" << "Счет получателя" << "Сумма" << "Подтвержден");

    for(int row = 0; row < mainAdmin->transferList->count(); row++)
    {
        QTableWidgetItem *index = new QTableWidgetItem(tr("%1").arg(mainAdmin->transferList->at(row)->getTransferId()));
        ui->TransferTable->setItem(row, 0, index);
        ui->TransferTable->item(row, 0)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *init = new QTableWidgetItem(tr("%1").arg(mainAdmin->transferList->at(row)->getInit()));
        ui->TransferTable->setItem(row, 1, init);
        ui->TransferTable->item(row, 1)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *sender = new QTableWidgetItem(tr("%1").arg(mainAdmin->transferList->at(row)->getSenderId()));
        ui->TransferTable->setItem(row, 2, sender);
        ui->TransferTable->item(row, 2)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *target = new QTableWidgetItem(tr("%1").arg(mainAdmin->transferList->at(row)->getTargetId()));
        ui->TransferTable->setItem(row, 3, target);
        ui->TransferTable->item(row, 3)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *sum = new QTableWidgetItem(tr("%1").arg(mainAdmin->transferList->at(row)->getSum()));
        ui->TransferTable->setItem(row, 4, sum);
        ui->TransferTable->item(row, 4)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *aprove = new QTableWidgetItem(tr("%1").arg(mainAdmin->transferList->at(row)->getAprove()));
        ui->TransferTable->setItem(row, 5, aprove);
        ui->TransferTable->item(row, 5)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);
    }
}

void AdminWindow::AdminErrorMsg(QString str)
{
    QMessageBox msg = QMessageBox();
    msg.setWindowIcon(QIcon(":/LoginImage/resource/images/mLkk-6k5vpA.png"));
    msg.setWindowTitle("Ошибка ввода");
    msg.setIcon(msg.Critical);
    msg.setText(str);
    msg.addButton("Принято", msg.AcceptRole);
    msg.exec();
}

void AdminWindow::AdminInformMsg(QString str)
{
    QMessageBox msg = QMessageBox();
    msg.setWindowIcon(QIcon(":/LoginImage/resource/images/mLkk-6k5vpA.png"));
    msg.setWindowTitle("Успѣхъ");
    msg.setIcon(msg.Information);
    msg.setText(str);
    msg.addButton("Принято", msg.AcceptRole);
    msg.exec();
}

AdminWindow::~AdminWindow()
{
    delete ui;
}


void AdminWindow::on_TransferCancle_clicked()
{
    Transfer* transfer = new Transfer();

    transfer->setTransferId(-1);
    for(int i = 0; i < mainAdmin->transferList->count(); i++)
        if(mainAdmin->transferList->at(i)->getTransferId() == ui->TransferBox->value())
            transfer = mainAdmin->transferList->at(i);


    if(transfer->getAprove() == "Cancled")
        AdminErrorMsg("Этотъ переводъ уже былъ отмѣненъ");
    else if(transfer->getAprove() == "User transfer" || transfer->getAprove() == "Cancle transfer")
    {
        adminAS->CancelCustomerTransfer(transfer, mainAdmin->getEmail());
        UpdateTransferTable();
        AdminInformMsg("Дѣйствіе по счету отмѣнено");
    }
    else if (transfer->getAprove() == "Waiting")
    {
        adminAS->CancleCorpTransfer(transfer->getTransferId());
        AdminInformMsg("Дѣйствіе по корпоративному счету отмѣнено");
    }
    else if (transfer->getTransferId() != -1)
    {
        bool check = true;
        for(int i = 0; i < banks->count(); i++)
            if (transfer->getInit() == banks->at(i)->getName())
                check = false;

        if(check)
        {
            adminAS->CancelCustomerTransfer(transfer, mainAdmin->getEmail());
            UpdateTransferTable();
            AdminInformMsg("Дѣйствіе по счету отмѣнено");
        }
        else

            AdminErrorMsg("Для отмѣны кредита используйте профильное окно");
    }
    else
        AdminErrorMsg("Невѣрный индексъ трансфера");

    UpdateTransferTable();
}


void AdminWindow::on_CreditCancle_clicked()
{
    int index = ui->CreditBox->value();
    Credit* credit = new Credit();
    credit->setCreditId(-1);

    for(int i = 0; i < mainAdmin->creditList->count(); i++)
        if(mainAdmin->creditList->at(i)->getCreditId() == index)
            credit = mainAdmin->creditList->at(i);

    if(credit->getCreditId() == -1)
         AdminErrorMsg("Невѣрный индексъ");
    else if(credit->getAproveStatus() == "Cancled")
        AdminErrorMsg("Данный кредитъ уже отмѣненъ");
    else if(credit->getAproveStatus() != "Waiting")
        adminAS->RejectCredit(index, "aprove");
    else
        adminAS->RejectCredit(index, "not aprove");

    UpdateCreditTable();
}


void AdminWindow::on_SalaryCancle_clicked()
{
    int index = ui->SalaryBox->value();
    SalaryProject* salary = new SalaryProject();
    salary->setIndex(-1);

    for(int i = 0; i < mainAdmin->salaryList->count(); i++)
        if(mainAdmin->salaryList->at(i)->getIndex() == index)
            salary = mainAdmin->salaryList->at(i);

    if(salary->getIndex() == -1)
         AdminErrorMsg("Невѣрный индексъ");
    else if(salary->getApproveStatus() == "Cancled")
        AdminErrorMsg("Данный ​зарплатный​ проектъ уже отмѣненъ");
    else
        adminAS->RejectSalaryProject(index, mainAdmin->getEmail());

    UpdateSalaryTable();
}


void AdminWindow::on_RejectUser_clicked()
{
    bool check = false;
    for(int i = 0; i < mainAdmin->userList->count(); i++)
        if(mainAdmin->userList->at(i)->getUserId() == ui->RejectUserBox->value())
            check = true;

    if(check)
    {
        adminAS->Ban(ui->RejectUserBox->value(), mainAdmin->getEmail());
        AdminInformMsg("Записка закрыта");
    }
    else
        AdminErrorMsg("Невѣрный индексъ записки");

    UpdateUserTable();
}


void AdminWindow::on_OpenUser_clicked()
{
    bool check = false;
    for(int i = 0; i < mainAdmin->userList->count(); i++)
        if(mainAdmin->userList->at(i)->getUserId() == ui->RejectUserBox->value())
            check = true;

    if(check)
    {
        adminAS->AproveCustomer(ui->RejectUserBox->value(), mainAdmin->getEmail());
        AdminInformMsg("Записка открыта");
    }
    else
        AdminErrorMsg("Невѣрный индексъ записки");

    UpdateUserTable();
}


void AdminWindow::on_Exit_clicked()
{
    LogInForm* login = new LogInForm();
    login->show();
    this->close();
}
