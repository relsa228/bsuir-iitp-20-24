#include "changepasswordview.h"
#include "ui_changepasswordview.h"

ChangePasswordView::ChangePasswordView(QString managerId, DatabaseService* dbService, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChangePasswordView)
{
    ui->setupUi(this);
    this->managerId = managerId;
    this->dbService = dbService;
}

ChangePasswordView::~ChangePasswordView()
{
    delete ui;
}

void ChangePasswordView::on_save_clicked()
{
    dbService->changeManagerPassword(managerId, ui->passwordEdit->text());
    this->close();
}

