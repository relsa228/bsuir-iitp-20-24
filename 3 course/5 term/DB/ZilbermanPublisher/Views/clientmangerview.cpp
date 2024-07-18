#include "clientmangerview.h"
#include "ui_clientmangerview.h"

ClientMangerView::ClientMangerView(DatabaseService *dbService, Manager *manager, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClientMangerView)
{
    ui->setupUi(this);

    this->dbService = dbService;
    this->wrkManager = manager;

    ui->name_lable->setText(wrkManager->getSurname() + " " + wrkManager->getName() + " " + wrkManager->getPatronymic());
    ui->id_lable->setText("ID: " + wrkManager->getId());

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(updateCustomerTab()));
    connect(timer, SIGNAL(timeout()), this, SLOT(updateOrderTab()));
    connect(timer, SIGNAL(timeout()), this, SLOT(updateAuthorTab()));
    connect(timer, SIGNAL(timeout()), this, SLOT(updateWorkTab()));
    timer->start(100);
}

ClientMangerView::~ClientMangerView()
{
    delete ui;
}

void ClientMangerView::on_add_author_clicked()
{
    AddAuthor* addAuthorView = new AddAuthor(dbService, wrkManager);
    addAuthorView->show();
}

void ClientMangerView::on_add_customer_clicked()
{
    AddCustomerView* addCustomerView = new AddCustomerView(dbService, wrkManager);
    addCustomerView->show();
}

void ClientMangerView::on_add_order_clicked()
{
    OrderView* orderView = new OrderView(dbService, wrkManager);
    orderView->show();
}

void ClientMangerView::updateAuthorTab()
{   
    QList<Author*>* authors = dbService->getAuthors();
    ui->author_table->setColumnCount(5);
    ui->author_table->setRowCount(authors->count());
    ui->author_table->setHorizontalHeaderLabels(QStringList() << "ID" << "Имя" << "Фамилия" << "Отчество" << "Кол-во работ");

    for(int row = 0; row < authors->count(); row++)
    {
        QTableWidgetItem *accName = new QTableWidgetItem(tr("%1").arg(authors->at(row)->getId()));
        ui->author_table->setItem(row, 0, accName);
        ui->author_table->item(row, 0)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *bank = new QTableWidgetItem(tr("%1").arg(authors->at(row)->getName()));
        ui->author_table->setItem(row, 1, bank);
        ui->author_table->item(row, 1)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *num = new QTableWidgetItem(tr("%1").arg(authors->at(row)->getSurname()));
        ui->author_table->setItem(row, 2, num);
        ui->author_table->item(row, 2)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *money = new QTableWidgetItem(tr("%1").arg(authors->at(row)->getPatronymic()));
        ui->author_table->setItem(row, 3, money);
        ui->author_table->item(row, 3)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *dedline = new QTableWidgetItem(tr("%1").arg(authors->at(row)->getWork_count()));
        ui->author_table->setItem(row, 4, dedline);
        ui->author_table->item(row, 4)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);
    }
}

void ClientMangerView::updateOrderTab()
{   
    QList<Order*>* orders = dbService->getOrders(wrkManager->getId());
    ui->order_table->setColumnCount(7);
    ui->order_table->setRowCount(orders->count());
    ui->order_table->setHorizontalHeaderLabels(QStringList() << "ID" << "Заказчик" << "Стоимость" << "Дата открытия" << "Краний срок" << "Дата закрытия" << "Статус");

    for(int row = 0; row < orders->count(); row++)
    {
        QTableWidgetItem *accName = new QTableWidgetItem(tr("%1").arg(orders->at(row)->getId()));
        ui->order_table->setItem(row, 0, accName);
        ui->order_table->item(row, 0)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *bank = new QTableWidgetItem(tr("%1").arg(orders->at(row)->getCustomer()));
        ui->order_table->setItem(row, 1, bank);
        ui->order_table->item(row, 1)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *num = new QTableWidgetItem(tr("%1").arg(orders->at(row)->getCost()));
        ui->order_table->setItem(row, 2, num);
        ui->order_table->item(row, 2)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *money = new QTableWidgetItem(tr("%1").arg(orders->at(row)->getOpen_date()));
        ui->order_table->setItem(row, 3, money);
        ui->order_table->item(row, 3)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *dedline = new QTableWidgetItem(tr("%1").arg(orders->at(row)->getDedline()));
        ui->order_table->setItem(row, 4, dedline);
        ui->order_table->item(row, 4)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *closeDate = new QTableWidgetItem(tr("%1").arg(orders->at(row)->getClose_date()));
        ui->order_table->setItem(row, 5, closeDate);
        ui->order_table->item(row, 5)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *state = new QTableWidgetItem(tr("%1").arg(orders->at(row)->getOrder_state()));
        ui->order_table->setItem(row, 6, state);
        ui->order_table->item(row, 6)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);
    }
}

void ClientMangerView::updateWorkTab()
{
    QList<Work*>* works = dbService->getWorks();
    ui->work_table->setColumnCount(5);
    ui->work_table->setRowCount(works->count());
    ui->work_table->setHorizontalHeaderLabels(QStringList() << "ID" << "Название" << "Издание" << "Тип" << "Жанры");

    for(int row = 0; row < works->count(); row++)
    {
        QString genres = "";
        for(Genre *genre: *works->at(row)->genres)
            genres += genre->getGenre() + ", ";

        genres.chop(2);

        QTableWidgetItem *accName = new QTableWidgetItem(tr("%1").arg(works->at(row)->getId()));
        ui->work_table->setItem(row, 0, accName);
        ui->work_table->item(row, 0)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *bank = new QTableWidgetItem(tr("%1").arg(works->at(row)->getName()));
        ui->work_table->setItem(row, 1, bank);
        ui->work_table->item(row, 1)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *num = new QTableWidgetItem(tr("%1").arg(works->at(row)->getEdition_number()));
        ui->work_table->setItem(row, 2, num);
        ui->work_table->item(row, 2)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *money = new QTableWidgetItem(tr("%1").arg(works->at(row)->getType()->getType()));
        ui->work_table->setItem(row, 3, money);
        ui->work_table->item(row, 3)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *dedline = new QTableWidgetItem(tr("%1").arg(genres));
        ui->work_table->setItem(row, 4, dedline);
        ui->work_table->item(row, 4)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);
    }
}

void ClientMangerView::updateCustomerTab()
{    
    QList<Customer*>* customers = dbService->getCustomersViaManager(wrkManager->getId());
    ui->customer_table->setColumnCount(4);
    ui->customer_table->setRowCount(customers->count());
    ui->customer_table->setHorizontalHeaderLabels(QStringList() << "ID" << "Название" << "Специализация" << "Кол-во заказов");

    for(int row = 0; row < customers->count(); row++)
    {
        QTableWidgetItem *accName = new QTableWidgetItem(tr("%1").arg(customers->at(row)->getId()));
        ui->customer_table->setItem(row, 0, accName);
        ui->customer_table->item(row, 0)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *bank = new QTableWidgetItem(tr("%1").arg(customers->at(row)->getName()));
        ui->customer_table->setItem(row, 1, bank);
        ui->customer_table->item(row, 1)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *num = new QTableWidgetItem(tr("%1").arg(customers->at(row)->getSpec()));
        ui->customer_table->setItem(row, 2, num);
        ui->customer_table->item(row, 2)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *money = new QTableWidgetItem(tr("%1").arg(customers->at(row)->getOrder_count()));
        ui->customer_table->setItem(row, 3, money);
        ui->customer_table->item(row, 3)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);
    }
}

void ClientMangerView::resizeEvent(QResizeEvent *)
{
    float newSizeCustomer = ui->customer_table->size().width()/4;
    if (newSizeCustomer > 33) {
        if(ui->customer_table->rowCount() == 0)
            for (int i = 0; i < 4; i++)
                ui->customer_table->setColumnWidth(i, newSizeCustomer);
        else
            for (int i = 0; i < 4; i++)
                ui->customer_table->setColumnWidth(i, newSizeCustomer - 6.5);
    }

    float newSizeOrder = ui->order_table->size().width()/7;
    if (newSizeOrder > 33) {
        if(ui->order_table->rowCount() == 0)
            for (int i = 0; i < 7; i++)
                ui->order_table->setColumnWidth(i, newSizeOrder);
        else
            for (int i = 0; i < 7; i++)
                ui->order_table->setColumnWidth(i, newSizeOrder - 6.5);
    }

    float newSizeAuthor = ui->author_table->size().width()/5;
    if (newSizeAuthor > 33) {
        if(ui->author_table->rowCount() == 0)
            for (int i = 0; i < 5; i++)
                ui->author_table->setColumnWidth(i, newSizeAuthor);
        else
            for (int i = 0; i < 5; i++)
                ui->author_table->setColumnWidth(i, newSizeAuthor - 6.5);
    }

    float newSizeWork = ui->work_table->size().width()/5;
    if (newSizeWork > 33) {
        if(ui->work_table->rowCount() == 0)
            for (int i = 0; i < 5; i++)
                ui->work_table->setColumnWidth(i, newSizeWork);
        else
            for (int i = 0; i < 5; i++)
                ui->work_table->setColumnWidth(i, newSizeWork - 6.5);
    }
}

void ClientMangerView::on_add_work_clicked()
{
    AddWork *addWork = new AddWork(dbService, wrkManager->getId());
    addWork->show();
}

void ClientMangerView::on_exit_clicked()
{
    LoginView* loginView = new LoginView();
    loginView->show();
    this->close();
}


void ClientMangerView::on_close_clicked()
{
     QList<Order*>* orders = dbService->getOrders(wrkManager->getId());
     int num = ui->close_box->value();

     if(orders->count() > num - 1)
        dbService->changeOrderStatus(orders->at(num - 1)->getId(), wrkManager->getId());
     else {
         QMessageBox msg = QMessageBox();
         msg.setWindowIcon(QIcon(":/Icons/MainIcon/Resources/MainIcons/free-icon-book-4341050.png"));
         msg.setWindowTitle("Ошибка ввода");
         msg.setIcon(msg.Critical);
         msg.setText("Заказа не существует");
         msg.addButton("Принято", msg.AcceptRole);
         msg.exec();
     }
}

