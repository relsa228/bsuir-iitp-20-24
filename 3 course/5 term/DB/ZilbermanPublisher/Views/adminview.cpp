#include "adminview.h"
#include "ui_adminview.h"

AdminView::AdminView(DatabaseService *dbService, Manager *manager, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminView)
{
    ui->setupUi(this);
    this->dbService = dbService;
    this->wrkManager = manager;
    this->positions = dbService->getPositions();

    ui->name_lable->setText(wrkManager->getSurname() + " " + wrkManager->getName() + " " + wrkManager->getPatronymic());
    ui->id_lable->setText("ID: " + wrkManager->getId());

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(updateManagerTable()));
    connect(timer, SIGNAL(timeout()), this, SLOT(updateLoggsTable()));
    timer->start(100);
}

AdminView::~AdminView()
{
    delete ui;
}

void AdminView::on_pushButton_clicked()
{
    LoginView* loginView = new LoginView();
    loginView->show();
    this->close();
}

void AdminView::updateManagerTable()
{
    managers = dbService->getManagers();
    ui->managers_table->setColumnCount(8);
    ui->managers_table->setRowCount(managers->count());
    ui->managers_table->setHorizontalHeaderLabels(QStringList() << "ID" << "Имя" << "Фамилия" << "Отчество" << "Имя пользователя"
                                                  << "Должность" << "Последняя авторизация" << "Блокировка");

    for(int row = 0; row < managers->count(); row++)
    {
        QString date = managers->at(row)->getLastAuthTime();
        date.replace("T", " ");
        QString isActive;
        if (managers->at(row)->getIs_active())
            isActive = "Нет";
        else
            isActive = "Да";

        QString position;
        for(Position* positionPtr: *positions)
            if (managers->at(row)->getPosition() == QString::number(positionPtr->getId()))
                position = positionPtr->getPosition();

        QTableWidgetItem *accName = new QTableWidgetItem(tr("%1").arg(managers->at(row)->getId()));
        ui->managers_table->setItem(row, 0, accName);
        ui->managers_table->item(row, 0)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *bank = new QTableWidgetItem(tr("%1").arg(managers->at(row)->getName()));
        ui->managers_table->setItem(row, 1, bank);
        ui->managers_table->item(row, 1)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *num = new QTableWidgetItem(tr("%1").arg(managers->at(row)->getSurname()));
        ui->managers_table->setItem(row, 2, num);
        ui->managers_table->item(row, 2)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *money = new QTableWidgetItem(tr("%1").arg(managers->at(row)->getPatronymic()));
        ui->managers_table->setItem(row, 3, money);
        ui->managers_table->item(row, 3)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *username = new QTableWidgetItem(tr("%1").arg(managers->at(row)->getUsername()));
        ui->managers_table->setItem(row, 4, username);
        ui->managers_table->item(row, 4)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *dedline = new QTableWidgetItem(tr("%1").arg(position));
        ui->managers_table->setItem(row, 5, dedline);
        ui->managers_table->item(row, 5)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *positionStr = new QTableWidgetItem(tr("%1").arg(date));
        ui->managers_table->setItem(row, 6, positionStr);
        ui->managers_table->item(row, 6)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *last_auth = new QTableWidgetItem(tr("%1").arg(isActive));
        ui->managers_table->setItem(row, 7, last_auth);
        ui->managers_table->item(row, 7)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);
    }
}

void AdminView::updateLoggsTable()
{
    QList<Log*> *logs = dbService->getLogs();
    ui->logging_table->setColumnCount(5);
    ui->logging_table->setRowCount(logs->count());
    ui->logging_table->setHorizontalHeaderLabels(QStringList() << "ID исполнителя" << "Действие" << "ID объекта" << "Тип объекта" << "Время");

    for(int row = 0; row < logs->count(); row++)
    {
        QTableWidgetItem *accName = new QTableWidgetItem(tr("%1").arg(logs->at(row)->getDoerId()));
        ui->logging_table->setItem(row, 0, accName);
        ui->logging_table->item(row, 0)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *bank = new QTableWidgetItem(tr("%1").arg(logs->at(row)->getAction()));
        ui->logging_table->setItem(row, 1, bank);
        ui->logging_table->item(row, 1)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *num = new QTableWidgetItem(tr("%1").arg(logs->at(row)->getObjectId()));
        ui->logging_table->setItem(row, 2, num);
        ui->logging_table->item(row, 2)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *money = new QTableWidgetItem(tr("%1").arg(logs->at(row)->getObjectType()));
        ui->logging_table->setItem(row, 3, money);
        ui->logging_table->item(row, 3)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *username = new QTableWidgetItem(tr("%1").arg(logs->at(row)->getCurrentTime()));
        ui->logging_table->setItem(row, 4, username);
        ui->logging_table->item(row, 4)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);
    }
}

void AdminView::resizeEvent(QResizeEvent *)
{
    float newSizeManagers = ui->managers_table->size().width()/8;
    if (newSizeManagers > 33) {
        if(ui->managers_table->rowCount() == 0)
            for (int i = 0; i < 8; i++)
                ui->managers_table->setColumnWidth(i, newSizeManagers);
        else
            for (int i = 0; i < 8; i++)
                ui->managers_table->setColumnWidth(i, newSizeManagers - 6.5);
    }

    float newSizeLogging = ui->logging_table->size().width()/5;
    if (newSizeLogging > 33) {
        if(ui->logging_table->rowCount() == 0)
            for (int i = 0; i < 5; i++)
                ui->logging_table->setColumnWidth(i, newSizeLogging);
        else
            for (int i = 0; i < 5; i++)
                ui->logging_table->setColumnWidth(i, newSizeLogging - 6.5);
    }
}

void AdminView::on_block_manager_clicked()
{
    QString managerId = "";
    int num = ui->choose_box->value() - 1;
    if(num < managers->count())
        managerId = managers->at(num)->getId();
    else {
        QMessageBox msg = QMessageBox();
        msg.setWindowIcon(QIcon(":/Icons/MainIcon/Resources/MainIcons/free-icon-book-4341050.png"));
        msg.setWindowTitle("Ошибка ввода");
        msg.setIcon(msg.Critical);
        msg.setText("Пользователя не существует");
        msg.addButton("Принято", msg.AcceptRole);
        msg.exec();
    }

    dbService->changeManagerStatus(managerId, "false");
}


void AdminView::on_unblock_manager_clicked()
{
    QString managerId = "";
    int num = ui->choose_box->value() - 1;
    if(num < managers->count())
        managerId = managers->at(num)->getId();
    else {
        QMessageBox msg = QMessageBox();
        msg.setWindowIcon(QIcon(":/Icons/MainIcon/Resources/MainIcons/free-icon-book-4341050.png"));
        msg.setWindowTitle("Ошибка ввода");
        msg.setIcon(msg.Critical);
        msg.setText("Пользователя не существует");
        msg.addButton("Принято", msg.AcceptRole);
        msg.exec();
    }

    dbService->changeManagerStatus(managerId, "true");
}


void AdminView::on_change_password_clicked()
{
    QString managerId = "";
    int num = ui->choose_box->value() - 1;
    if(num < managers->count())
        managerId = managers->at(num)->getId();
    else {
        QMessageBox msg = QMessageBox();
        msg.setWindowIcon(QIcon(":/Icons/MainIcon/Resources/MainIcons/free-icon-book-4341050.png"));
        msg.setWindowTitle("Ошибка ввода");
        msg.setIcon(msg.Critical);
        msg.setText("Пользователя не существует");
        msg.addButton("Принято", msg.AcceptRole);
        msg.exec();
    }

    ChangePasswordView* chPass = new ChangePasswordView(managerId, dbService);
    chPass->show();
}


void AdminView::on_add_new_clicked()
{
    AddManager* addManager = new AddManager(dbService);
    addManager->show();
}

