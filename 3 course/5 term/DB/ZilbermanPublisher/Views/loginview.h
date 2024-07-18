#ifndef LOGINVIEW_H
#define LOGINVIEW_H

#include <QMainWindow>
#include <QMessageBox>

#include <Services/databaseservice.h>

#include <Entities/manager.h>

#include <Views/clientmangerview.h>
#include <Views/printcentermanagerview.h>
#include <Views/adminview.h>

namespace Ui {
class LoginView;
}

class LoginView : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginView(QWidget *parent = nullptr);
    ~LoginView();

private slots:
    void on_pushButton_clicked();

private:
    Ui::LoginView *ui;
    DatabaseService* dbService;
};

#endif // LOGINVIEW_H
