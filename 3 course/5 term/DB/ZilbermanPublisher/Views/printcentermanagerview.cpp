#include "printcentermanagerview.h"
#include "ui_printcentermanagerview.h"

PrintCenterManagerView::PrintCenterManagerView(DatabaseService *dbService, Manager *manager, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PrintCenterManagerView)
{
    ui->setupUi(this);
    this->dbService = dbService;
    this->wrkManager = manager;
    printCenter = dbService->getPrintCenterViaManager(wrkManager);
    this->onWorkBatches = dbService->getOnWorkBatches(printCenter->getId());
    this->readyBatches = dbService->getReadyBatches(printCenter->getId());

    ui->name_lable->setText(wrkManager->getSurname() + " " + wrkManager->getName() + " " + wrkManager->getPatronymic());
    ui->id_lable->setText("ID: " + wrkManager->getId());
    ui->address_lable->setText("Адрес печатного центра: " + printCenter->getAdress());
    ui->order_count_lable->setText("Выполнено работ: " + QString::number(printCenter->getPublication_batch()));

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(updateOnWorkTable()));
    connect(timer, SIGNAL(timeout()), this, SLOT(updateReadyTable()));
    timer->start(100);
}

PrintCenterManagerView::~PrintCenterManagerView()
{
    delete ui;
}

void PrintCenterManagerView::on_start_work_clicked()
{
    int num = ui->start_box->value() - 1;
    if (num < onWorkBatches->count())
        dbService->changeBatchPrintStatus(onWorkBatches->at(num)->getId(), "4", wrkManager->getId());
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

void PrintCenterManagerView::updateOnWorkTable()
{
    printCenter = dbService->getPrintCenterViaManager(wrkManager);
    ui->order_count_lable->setText("Выполнено работ: " + QString::number(printCenter->getPublication_batch()));

    this->onWorkBatches = dbService->getOnWorkBatches(printCenter->getId());

    ui->on_work_table->setColumnCount(3);
    ui->on_work_table->setRowCount(onWorkBatches->count());
    ui->on_work_table->setHorizontalHeaderLabels(QStringList() << "ID заказа" << "ID Произведение" << "Кол-во копий");

    for(int row = 0; row < onWorkBatches->count(); row++)
    {
        QTableWidgetItem *accName = new QTableWidgetItem(tr("%1").arg(onWorkBatches->at(row)->getOrder()));
        ui->on_work_table->setItem(row, 0, accName);
        ui->on_work_table->item(row, 0)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *bank = new QTableWidgetItem(tr("%1").arg(onWorkBatches->at(row)->getWork()));
        ui->on_work_table->setItem(row, 1, bank);
        ui->on_work_table->item(row, 1)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *num = new QTableWidgetItem(tr("%1").arg(onWorkBatches->at(row)->getCount_of_work()));
        ui->on_work_table->setItem(row, 2, num);
        ui->on_work_table->item(row, 2)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);
    }
}

void PrintCenterManagerView::updateReadyTable()
{
    this->readyBatches = dbService->getReadyBatches(printCenter->getId());

    ui->ready_table->setColumnCount(3);
    ui->ready_table->setRowCount(readyBatches->count());
    ui->ready_table->setHorizontalHeaderLabels(QStringList() << "ID заказа" << "ID Произведение" << "Кол-во копий");

    for(int row = 0; row < readyBatches->count(); row++)
    {
        QTableWidgetItem *accName = new QTableWidgetItem(tr("%1").arg(readyBatches->at(row)->getOrder()));
        ui->ready_table->setItem(row, 0, accName);
        ui->ready_table->item(row, 0)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *bank = new QTableWidgetItem(tr("%1").arg(readyBatches->at(row)->getWork()));
        ui->ready_table->setItem(row, 1, bank);
        ui->ready_table->item(row, 1)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);

        QTableWidgetItem *num = new QTableWidgetItem(tr("%1").arg(readyBatches->at(row)->getCount_of_work()));
        ui->ready_table->setItem(row, 2, num);
        ui->ready_table->item(row, 2)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);
    }
}

void PrintCenterManagerView::on_deny_work_clicked()
{
    int num = ui->deny_box->value() - 1;
    if (num < readyBatches->count())
        dbService->changeBatchPrintStatus(readyBatches->at(num)->getId(), "3", wrkManager->getId());
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

void PrintCenterManagerView::on_exit_clicked()
{
    LoginView* loginView = new LoginView();
    loginView->show();
    this->close();
}

void PrintCenterManagerView::resizeEvent(QResizeEvent *)
{
    float newSizeOnWork = ui->on_work_table->size().width()/3;
    if (newSizeOnWork > 33) {
        if(ui->on_work_table->rowCount() == 0)
            for (int i = 0; i < 3; i++)
                ui->on_work_table->setColumnWidth(i, newSizeOnWork);
        else
            for (int i = 0; i < 3; i++)
                ui->on_work_table->setColumnWidth(i, newSizeOnWork - 6.5);
    }

    float newSizeReady = ui->ready_table->size().width()/3;
    if (newSizeReady > 33) {
        if(ui->ready_table->rowCount() == 0)
            for (int i = 0; i < 3; i++)
                ui->ready_table->setColumnWidth(i, newSizeReady);
        else
            for (int i = 0; i < 3; i++)
                ui->ready_table->setColumnWidth(i, newSizeReady - 6.5);
    }
}
