QT       += core gui
QT       += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Entities/process.cpp \
    Services/Messages/errormsgservice.cpp \
    Services/Messages/infomsgservice.cpp \
    Services/processservice.cpp \
    Services/reportservice.cpp \
    Services/tableservice.cpp \
    main.cpp \
    taskwindow.cpp

HEADERS += \
    Entities/process.h \
    Services/Messages/errormsgservice.h \
    Services/Messages/infomsgservice.h \
    Services/processservice.h \
    Services/reportservice.h \
    Services/tableservice.h \
    taskwindow.h

FORMS += \
    taskwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resourses/icons.qrc
