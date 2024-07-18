#include "addmanager.h"
#include "ui_addmanager.h"

AddManager::AddManager(DatabaseService* dbService, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddManager)
{
    ui->setupUi(this);
    this->dbService = dbService;

    QList<Position*> *positions = dbService->getPositions();
    QStringList* posList = new QStringList();
    for(Position* position: *positions)
        posList->push_back(position->getPosition());

    ui->positionBox->addItems(*posList);
}

AddManager::~AddManager()
{
    delete ui;
}

void AddManager::on_save_clicked()
{
    QString position = ui->positionBox->currentText();
    QList<Position*> *positions = dbService->getPositions();
    for(Position* pos: *positions)
        if (pos->getPosition() == position)
            position = QString::number(pos->getId());
    Manager* manager = new Manager(ui->nameEdit->text(), ui->surEdit->text(), ui->patrEdit->text(), ui->usernameEdit->text(), position);

    dbService->addManager(manager, ui->passwordEdit->text());
    this->close();
}

