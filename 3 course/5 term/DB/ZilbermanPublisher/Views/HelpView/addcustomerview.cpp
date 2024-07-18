#include "addcustomerview.h"
#include "ui_addcustomerview.h"

AddCustomerView::AddCustomerView(DatabaseService *dbService, Manager *manager, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddCustomerView)
{
    ui->setupUi(this);

    this->dbService = dbService;
    this->wrkManager = manager;
}

AddCustomerView::~AddCustomerView()
{
    delete ui;
}

void AddCustomerView::on_pushButton_clicked()
{
    QString name = ui->name_edit->text();
    QString spec = ui->spec_edit->text();

    dbService->addCustomer(name, spec, wrkManager->getId());

    this->close();
}

