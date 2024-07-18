#ifndef ADDMANAGER_H
#define ADDMANAGER_H

#include <QMainWindow>

#include <Entities/manager.h>
#include <Entities/position.h>

#include <Services/databaseservice.h>

namespace Ui {
class AddManager;
}

class AddManager : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddManager(DatabaseService* dbService, QWidget *parent = nullptr);
    ~AddManager();

private slots:
    void on_save_clicked();

private:
    Ui::AddManager *ui;

    DatabaseService *dbService;
};

#endif // ADDMANAGER_H
