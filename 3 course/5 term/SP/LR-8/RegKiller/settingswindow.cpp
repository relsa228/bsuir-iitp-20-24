#include "settingswindow.h"
#include "ui_settingswindow.h"

SettingsWindow::SettingsWindow(HKEY *option, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);

    wrkOption = option;

    if(*wrkOption == HKEY_CLASSES_ROOT)
        ui->ClassesRootRad->setChecked(true);
    if(*wrkOption == HKEY_CURRENT_USER)
        ui->CurrentUserRad->setChecked(true);
    if(*wrkOption == HKEY_LOCAL_MACHINE)
        ui->LocalMachineRad->setChecked(true);
    if(*wrkOption == HKEY_USERS)
        ui->UsersRad->setChecked(true);
    if(*wrkOption == HKEY_CURRENT_CONFIG)
        ui->CurrentConfigRad->setChecked(true);
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

void SettingsWindow::on_buttonBox_accepted()
{
    if(ui->ClassesRootRad->isChecked())
        *wrkOption = HKEY_CLASSES_ROOT;
    if(ui->CurrentUserRad->isChecked())
        *wrkOption = HKEY_CURRENT_USER;
    if(ui->LocalMachineRad->isChecked())
        *wrkOption = HKEY_LOCAL_MACHINE;
    if(ui->UsersRad->isChecked())
        *wrkOption = HKEY_USERS;
    if(ui->CurrentConfigRad->isChecked())
        *wrkOption = HKEY_CURRENT_CONFIG;

    this->close();
}


void SettingsWindow::on_buttonBox_rejected()
{
    this->close();
}

