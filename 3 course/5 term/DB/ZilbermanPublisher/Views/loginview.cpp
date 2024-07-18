#include "loginview.h"
#include "ui_loginview.h"

LoginView::LoginView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginView)
{
    ui->setupUi(this);
    dbService = new DatabaseService();
}

LoginView::~LoginView()
{
    delete ui;
}

void LoginView::on_pushButton_clicked()
{
    QString login = ui->username_edit->text();
    QString password = ui->password_edit->text();

    Manager *loginUser = dbService->getManager(login, password);
    if (loginUser == NULL)
        return;

    if(!loginUser->getIs_active()) {
        QMessageBox msg = QMessageBox();
        msg.setWindowIcon(QIcon(":/Icons/MainIcon/Resources/MainIcons/free-icon-book-4341050.png"));
        msg.setWindowTitle("Ошибка");
        msg.setIcon(msg.Critical);
        msg.setText("Учетная запись заблокирована");
        msg.addButton("Принято", msg.AcceptRole);
        msg.exec();
        return;
    }

    QMessageBox msg = QMessageBox();
    msg.setWindowIcon(QIcon(":/Icons/MainIcon/Resources/MainIcons/free-icon-book-4341050.png"));
    msg.setWindowTitle("Добро пожаловать");
    msg.setIcon(msg.Information);
    msg.setText("Здравствуйте, " + loginUser->getName() + " " + loginUser->getPatronymic() + "!");
    msg.addButton("Принято", msg.AcceptRole);
    msg.exec();

    if(loginUser->getPosition() == "Client manager") {
        ClientMangerView *clientView = new ClientMangerView(this->dbService, loginUser);
        clientView->show();
    }
    else if(loginUser->getPosition() == "Print center manager") {
        PrintCenterManagerView *printCenterView = new PrintCenterManagerView(this->dbService, loginUser);
        printCenterView->show();
    }
    else if(loginUser->getPosition() == "Administrator") {
        AdminView *adminView = new AdminView(this->dbService, loginUser);
        adminView->show();
    }

    dbService->updateLastAuthTime(loginUser->getId());
    this->close();
}

