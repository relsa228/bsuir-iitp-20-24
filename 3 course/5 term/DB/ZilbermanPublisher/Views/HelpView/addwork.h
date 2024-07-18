#ifndef ADDWORK_H
#define ADDWORK_H

#include "Services/databaseservice.h"
#include "qtablewidget.h"
#include <QMainWindow>

#include "Entities/genre.h"
#include "Entities/worktype.h"

namespace Ui {
class AddWork;
}

class AddWork : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddWork(DatabaseService *dbService, QString mangerId, QWidget *parent = nullptr);
    ~AddWork();

private slots:
    void on_add_author_clicked();

    void on_add_genre_clicked();

    void on_del_author_clicked();

    void on_del_genre_clicked();

    void on_add_work_clicked();

    virtual void resizeEvent(QResizeEvent *);

private:
    Ui::AddWork *ui;

    DatabaseService *dbService;

    QList<Author*> *authors;
    QList<Genre*> *genres;
    QList<WorkType*> *workTypes;

    QString mangerId;
    Work* newWork;
};

#endif // ADDWORK_H
