QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Entities/bank.cpp \
    Entities/bankaccount.cpp \
    Entities/company.cpp \
    Entities/credit.cpp \
    Entities/creditcircs.cpp \
    Entities/salaryproject.cpp \
    Entities/transfer.cpp \
    Entities/user.cpp \
    Forms/LilForms/addacc.cpp \
    Forms/LilForms/companytransferdialog.cpp \
    Forms/LilForms/creditdialog.cpp \
    Forms/LilForms/inoutdialog.cpp \
    Forms/LilForms/salarydialog.cpp \
    Forms/LilForms/transferdialog.cpp \
    Forms/adminwindow.cpp \
    Forms/custwindow.cpp \
    Forms/loginform.cpp \
    Forms/managerwindow.cpp \
    Forms/operatorwindow.cpp \
    Forms/registrationform.cpp \
    Forms/specwindow.cpp \
    Roles/administrator.cpp \
    Roles/customer.cpp \
    Roles/enterprisespecialist.cpp \
    Roles/manager.cpp \
    Roles/operator.cpp \
    Srvices/administratorservice.cpp \
    Srvices/customerservice.cpp \
    Srvices/databaseservice.cpp \
    Srvices/enterpricespecialistservice.cpp \
    Srvices/managerservice.cpp \
    Srvices/operatorservice.cpp \
    main.cpp

HEADERS += \
    Entities/bank.h \
    Entities/bankaccount.h \
    Entities/company.h \
    Entities/credit.h \
    Entities/creditcircs.h \
    Entities/salaryproject.h \
    Entities/transfer.h \
    Entities/user.h \
    Forms/LilForms/addacc.h \
    Forms/LilForms/companytransferdialog.h \
    Forms/LilForms/creditdialog.h \
    Forms/LilForms/inoutdialog.h \
    Forms/LilForms/salarydialog.h \
    Forms/LilForms/transferdialog.h \
    Forms/adminwindow.h \
    Forms/custwindow.h \
    Forms/loginform.h \
    Forms/managerwindow.h \
    Forms/operatorwindow.h \
    Forms/registrationform.h \
    Forms/specwindow.h \
    Roles/administrator.h \
    Roles/customer.h \
    Roles/enterprisespecialist.h \
    Roles/manager.h \
    Roles/operator.h \
    Srvices/administratorservice.h \
    Srvices/customerservice.h \
    Srvices/databaseservice.h \
    Srvices/enterpricespecialistservice.h \
    Srvices/managerservice.h \
    Srvices/operatorservice.h \
    obfuscate.h

FORMS += \
    Forms/LilForms/addacc.ui \
    Forms/LilForms/companytransferdialog.ui \
    Forms/LilForms/creditdialog.ui \
    Forms/LilForms/inoutdialog.ui \
    Forms/LilForms/salarydialog.ui \
    Forms/LilForms/transferdialog.ui \
    Forms/adminwindow.ui \
    Forms/custwindow.ui \
    Forms/loginform.ui \
    Forms/managerwindow.ui \
    Forms/operatorwindow.ui \
    Forms/registrationform.ui \
    Forms/specwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Images.qrc
