#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <windows.h>
#include <QDialog>

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsWindow(HKEY *option, QWidget *parent = nullptr);
    ~SettingsWindow();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::SettingsWindow *ui;
    HKEY *wrkOption;
};

#endif // SETTINGSWINDOW_H
