#include "orderview.h"
#include "ui_orderview.h"

OrderView::OrderView(DatabaseService *dbService, Manager *manager, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OrderView)
{
    ui->setupUi(this);

    this->dbService = dbService;
    this->wrkManager = manager;
    batches = new QList<Batch*>();

    ui->dedline_edit->setDate(QDate::currentDate());
    ui->batches_table->setColumnCount(3);
    ui->batches_table->setHorizontalHeaderLabels(QStringList() << "Работа" << "Кол-во копий" << "Печатный центр");

    QList<Customer*>* customers = dbService->getCustomersViaManager(manager->getId());

    QStringList* custList = new QStringList();
    for(Customer* customer: *customers)
        custList->push_back(customer->getName());

    ui->customer_box->addItems(*custList);

    uuid = QUuid::createUuid().toString();
    uuid.remove("}");
    uuid.remove("{");
}

OrderView::~OrderView()
{
    delete ui;
}

void OrderView::on_pushButton_3_clicked()
{
    QString customerName = ui->customer_box->currentText();
    QString customerID = "";
    QList<Customer*>* customers = dbService->getCustomersViaManager(wrkManager->getId());
    for(Customer* customer: *customers)
        if(customer->getName() == customerName)
            customerID = customer->getId();

    orderModel = new Order(uuid, customerID, ui->price_edit->value(), "", ui->dedline_edit->text().replace(".", "-"), "", "");
    orderModel->batches = batches;
    dbService->createOrder(orderModel, wrkManager->getId());
    this->close();
}


void OrderView::on_add_batch_clicked()
{
    BatchesView* batchesView = new BatchesView(ui->batches_table, dbService, batches, uuid);
    batchesView->show();
}


void OrderView::on_delete_batch_clicked()
{
    int num = ui->del_edit->value();
    if (num - 1 < batches->count()) {
        batches->removeAt(num - 1);
        ui->batches_table->removeRow(num - 1);
    }
    else {
        QMessageBox msg = QMessageBox();
        msg.setWindowIcon(QIcon(":/Icons/MainIcon/Resources/MainIcons/free-icon-book-4341050.png"));
        msg.setWindowTitle("Ошибка ввода");
        msg.setIcon(msg.Critical);
        msg.setText("Партии не существует");
        msg.addButton("Принято", msg.AcceptRole);
        msg.exec();
    }
}

void OrderView::resizeEvent(QResizeEvent *)
{
    float newSizeBatches = ui->batches_table->size().width()/3;
    if (newSizeBatches > 33) {
        if(ui->batches_table->rowCount() == 0)
            for (int i = 0; i < 3; i++)
                ui->batches_table->setColumnWidth(i, newSizeBatches);
        else
            for (int i = 0; i < 3; i++)
                ui->batches_table->setColumnWidth(i, newSizeBatches - 6.5);
    }
}

