#include "infomsgservice.h"

InfoMsgService::InfoMsgService(QString message)
{
    QMessageBox msg = QMessageBox();
    msg.setWindowIcon(QIcon(":/icons/icons/terminal-fill.svg"));
    msg.setWindowTitle("Выполнено");
    msg.setIcon(msg.Information);
    msg.setText(message);
    msg.addButton("Принято", msg.AcceptRole);
    msg.exec();
}
