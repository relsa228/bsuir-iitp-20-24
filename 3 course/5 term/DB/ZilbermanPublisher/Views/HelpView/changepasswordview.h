#ifndef CHANGEPASSWORDVIEW_H
#define CHANGEPASSWORDVIEW_H

#include <QMainWindow>
#include <QString>

#include <Services/databaseservice.h>

namespace Ui {
class ChangePasswordView;
}

class ChangePasswordView : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChangePasswordView(QString managerId, DatabaseService* dbService, QWidget *parent = nullptr);
    ~ChangePasswordView();

private slots:
    void on_save_clicked();

private:
    Ui::ChangePasswordView *ui;

    QString managerId;
    DatabaseService* dbService;
};

#endif // CHANGEPASSWORDVIEW_H
