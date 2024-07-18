#ifndef BATCHESVIEW_H
#define BATCHESVIEW_H

#include <QMainWindow>
#include <QTableWidget>

#include <Entities/order.h>
#include <Entities/work.h>
#include "Entities/printcenter.h"

#include <Services/databaseservice.h>

namespace Ui {
class BatchesView;
}

class BatchesView : public QMainWindow
{
    Q_OBJECT

public:
    explicit BatchesView(QTableWidget *table, DatabaseService *dbService, QList<Batch*>* batches, QString uuid, QWidget *parent = nullptr);
    ~BatchesView();

private slots:
    void on_add_batch_clicked();

private:
    Ui::BatchesView *ui;

    QString uuid;

    QList<Batch*> *batches;
    QList<Work*>* works;
    QList<PrintCenter*> *printcenters;

    DatabaseService *dbService;
    QTableWidget *wrkTable;
};

#endif // BATCHESVIEW_H
