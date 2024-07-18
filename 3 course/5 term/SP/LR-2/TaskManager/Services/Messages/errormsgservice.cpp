#include "errormsgservice.h"

ErrorMsgService::ErrorMsgService(QString message)
{
    QMessageBox msg = QMessageBox();
    msg.setWindowIcon(QIcon(":/icons/icons/terminal-fill.svg"));
    msg.setWindowTitle("Ошибка");
    msg.setIcon(msg.Critical);
    msg.setText(message);
    msg.addButton("Принято", msg.AcceptRole);
    msg.exec();
}
