#ifndef ADDAUTHOR_H
#define ADDAUTHOR_H

#include <QMainWindow>
#include <QTableWidget>

#include <Services/databaseservice.h>

#include <Entities/manager.h>
#include <Entities/author.h>
#include <Entities/work.h>

namespace Ui {
class AddAuthor;
}

class AddAuthor : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddAuthor(DatabaseService *dbService, Manager *manager, QWidget *parent = nullptr);
    ~AddAuthor();

private slots:
    void on_add_author_clicked();

private:
    Ui::AddAuthor *ui;

    DatabaseService *dbService;
    Manager *wrkManager;
};

#endif // ADDAUTHOR_H
