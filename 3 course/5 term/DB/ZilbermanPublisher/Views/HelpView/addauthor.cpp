#include "addauthor.h"
#include "ui_addauthor.h"

AddAuthor::AddAuthor(DatabaseService *dbService, Manager *manager, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddAuthor)
{
    ui->setupUi(this);

    this->dbService = dbService;
    this->wrkManager = manager;
}

AddAuthor::~AddAuthor()
{
    delete ui;
}

void AddAuthor::on_add_author_clicked()
{
    QString name = ui->name_edit->text();
    QString surname = ui->surname_edit->text();
    QString ptr = ui->ptr_edit->text();

    dbService->addAuthor(name, surname, ptr, wrkManager->getId());
    this->close();
}

