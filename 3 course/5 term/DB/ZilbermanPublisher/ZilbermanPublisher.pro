QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Entities/author.cpp \
    Entities/batch.cpp \
    Entities/customer.cpp \
    Entities/genre.cpp \
    Entities/log.cpp \
    Entities/manager.cpp \
    Entities/order.cpp \
    Entities/position.cpp \
    Entities/printcenter.cpp \
    Entities/work.cpp \
    Entities/worktype.cpp \
    Services/databaseservice.cpp \
    Services/loggerservice.cpp \
    Views/HelpView/addauthor.cpp \
    Views/HelpView/addcustomerview.cpp \
    Views/HelpView/addmanager.cpp \
    Views/HelpView/addwork.cpp \
    Views/HelpView/batchesview.cpp \
    Views/HelpView/changepasswordview.cpp \
    Views/HelpView/orderview.cpp \
    Views/adminview.cpp \
    Views/clientmangerview.cpp \
    Views/loginview.cpp \
    Views/printcentermanagerview.cpp \
    main.cpp

HEADERS += \
    Entities/author.h \
    Entities/batch.h \
    Entities/customer.h \
    Entities/genre.h \
    Entities/log.h \
    Entities/manager.h \
    Entities/order.h \
    Entities/position.h \
    Entities/printcenter.h \
    Entities/work.h \
    Entities/worktype.h \
    Services/databaseservice.h \
    Services/loggerservice.h \
    Views/HelpView/addauthor.h \
    Views/HelpView/addcustomerview.h \
    Views/HelpView/addmanager.h \
    Views/HelpView/addwork.h \
    Views/HelpView/batchesview.h \
    Views/HelpView/changepasswordview.h \
    Views/HelpView/orderview.h \
    Views/adminview.h \
    Views/clientmangerview.h \
    Views/loginview.h \
    Views/printcentermanagerview.h

FORMS += \
    Views/HelpView/addauthor.ui \
    Views/HelpView/addcustomerview.ui \
    Views/HelpView/addmanager.ui \
    Views/HelpView/addwork.ui \
    Views/HelpView/batchesview.ui \
    Views/HelpView/changepasswordview.ui \
    Views/HelpView/orderview.ui \
    Views/adminview.ui \
    Views/clientmangerview.ui \
    Views/loginview.ui \
    Views/printcentermanagerview.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Icons.qrc
