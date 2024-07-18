#include "specwindow.h"
#include "ui_specwindow.h"

//Сервисы
DataBaseService* specDB = new DataBaseService();
EnterpriceSpecialistService* specES = new EnterpriceSpecialistService();
//Переменные
EnterpriseSpecialist* workSpec;

SpecWindow::SpecWindow(EnterpriseSpecialist* enterpriseSpetialist, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SpecWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/LoginImage/resource/images/mLkk-6k5vpA.png"));
    setWindowTitle("Imperial banking system");

    workSpec = enterpriseSpetialist;
    workSpec->setCompany(specDB->GetCompany(workSpec->getCompanyName()));

    ui->AproveIndex->setMaximum(100000000);
    ui->CompanyName->setText(workSpec->getCompanyName());
    UpdateSalaryTable();
    UpdateAccTable();
}

void SpecWindow::UpdateSalaryTable()
{
    workSpec->salaryList = new QList<SalaryProject*>;
    QList<SalaryProject*>* salaryList = specDB->GetSalaryProjects(workSpec->getCompanyName());

    for(int i = 0; i < salaryList->count(); i++)
        if(salaryList->at(i)->getApproveStatus() == "Waiting for a documents")
            workSpec->salaryList->push_back(salaryList->at(i));

    ui->SalaryTable->setColumnCount(4);

    for (int i = 0; i < 4; i++)
        ui->SalaryTable->setColumnWidth(i, 130);

    ui->SalaryTable->setRowCount(workSpec->salaryList->count());
    ui->SalaryTable->setHorizontalHeaderLabels(QStringList()<< "Индекс проекта" << "БИК банка" << "Кто предложил" << "Статус");

    for(int row = 0; row < workSpec->salaryList->count(); row++)
    {
        QTableWidgetItem *index = new QTableWidgetItem(tr("%1").arg( workSpec->salaryList->at(row)->getIndex()));
        ui->SalaryTable->setItem(row, 0, index);
        ui->SalaryTable->item(row, 0)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *BIK = new QTableWidgetItem(tr("%1").arg( workSpec->salaryList->at(row)->getBIK()));
        ui->SalaryTable->setItem(row, 1, BIK);
        ui->SalaryTable->item(row, 1)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *UserName = new QTableWidgetItem(tr("%1").arg( workSpec->salaryList->at(row)->getUsername()));
        ui->SalaryTable->setItem(row, 2, UserName);
        ui->SalaryTable->item(row, 2)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *Status = new QTableWidgetItem(tr("%1").arg( workSpec->salaryList->at(row)->getApproveStatus()));
        ui->SalaryTable->setItem(row, 3, Status);
        ui->SalaryTable->item(row, 3)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);
    }
}

void SpecWindow::UpdateAccTable()
{
    QList<BankAccount*>* bankAccList = specDB->GetBankAccounts(workSpec->getCompanyName());

    ui->AccTable->setColumnCount(4);

    for (int i = 0; i < 4; i++)
        ui->AccTable->setColumnWidth(i, 130);

    ui->AccTable->setRowCount(bankAccList->count());
    ui->AccTable->setHorizontalHeaderLabels(QStringList() << "Имя" << "Банк" << "Номер счета" << "Баланс");

    for(int row = 0; row <bankAccList->count(); row++)
    {
        QTableWidgetItem *accName = new QTableWidgetItem(tr("%1").arg(bankAccList->at(row)->getAccName()));
        ui->AccTable->setItem(row, 0, accName);
        ui->AccTable->item(row, 0)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *bank = new QTableWidgetItem(tr("%1").arg(bankAccList->at(row)->getBankName()));
        ui->AccTable->setItem(row, 1, bank);
        ui->AccTable->item(row, 1)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *num = new QTableWidgetItem(tr("%1").arg(bankAccList->at(row)->getAccId()));
        ui->AccTable->setItem(row, 2, num);
        ui->AccTable->item(row, 2)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *money = new QTableWidgetItem(tr("%1").arg(bankAccList->at(row)->getMoney()));
        ui->AccTable->setItem(row, 3, money);
        ui->AccTable->item(row, 3)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);
    }
}

void SpecWindow::SpecErrorMessage(QString str)
{
    QMessageBox msg = QMessageBox();
    msg.setWindowIcon(QIcon(":/LoginImage/resource/images/mLkk-6k5vpA.png"));
    msg.setWindowTitle("Ошибка ввода");
    msg.setIcon(msg.Critical);
    msg.setText(str);
    msg.addButton("Принято", msg.AcceptRole);
    msg.exec();
}

void SpecWindow::SpecInformMessage(QString str)
{
    QMessageBox msg = QMessageBox();
    msg.setWindowIcon(QIcon(":/LoginImage/resource/images/mLkk-6k5vpA.png"));
    msg.setWindowTitle("Успѣхъ");
    msg.setIcon(msg.Information);
    msg.setText(str);
    msg.addButton("Принято", msg.AcceptRole);
    msg.exec();
}

SpecWindow::~SpecWindow()
{
    delete ui;
}

void SpecWindow::on_AproveSalary_clicked()
{
    int salaryIndex = ui->AproveIndex->value();
    bool check = false;

    for(int i = 0; i < workSpec->salaryList->count(); i++)
        if(workSpec->salaryList->at(i)->getIndex() == salaryIndex)
            check = true;

    if(check)
    {
        specES->AproveSalaryProject(salaryIndex, workSpec->getEmail());
        UpdateSalaryTable();

        SpecInformMessage("Документы отправлены системѣ");
    }
    else
        SpecErrorMessage("Невѣрный индексъ зарплатного проекта");
}


void SpecWindow::on_Exit_clicked()
{
    LogInForm* login = new LogInForm();
    login->show();
    this->close();
}


void SpecWindow::on_AddTransfer_clicked()
{
    CompanyTransferDialog* companyTransfer = new CompanyTransferDialog(workSpec);
    companyTransfer->show();
    this->close();
}

