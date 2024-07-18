QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DefaultFigure/defaultellipse.cpp \
    DefaultFigure/defaultline.cpp \
    DefaultFigure/defaultpath.cpp \
    DefaultFigure/defaultplot.cpp \
    DefaultFigure/defaultrectangle.cpp \
    Entities/paintscene.cpp \
    Entities/picmanfigurefactory.cpp \
    Entities/picmanfiguresserializer.cpp \
    Entities/picmanlibrariesextracter.cpp \
    Forms/customwindow.cpp \
    Forms/drawingwindow.cpp \
    Forms/thicknessform.cpp \
    Tools/brush.cpp \
    Tools/eraser.cpp \
    Tools/filltool.cpp \
    main.cpp

HEADERS += \
    DefaultFigure/defaultellipse.h \
    DefaultFigure/defaultline.h \
    DefaultFigure/defaultpath.h \
    DefaultFigure/defaultplot.h \
    DefaultFigure/defaultrectangle.h \
    Entities/paintscene.h \
    Entities/picmanfigurefactory.h \
    Entities/picmanfiguresserializer.h \
    Entities/picmanlibrariesextracter.h \
    Forms/customwindow.h \
    Forms/drawingwindow.h \
    Forms/thicknessform.h \
    Tools/brush.h \
    Tools/eraser.h \
    Tools/filltool.h

FORMS += \
    Forms/customwindow.ui \
    Forms/drawingwindow.ui \
    Forms/thicknessform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources/Icons.qrc \
    Resources/Logo.qrc

win32: LIBS += -L$$PWD/SystemPackages/DefaultPicmanFigure/lib/ -lDefaultPicManFigure

INCLUDEPATH += $$PWD/SystemPackages/DefaultPicmanFigure/include
DEPENDPATH += $$PWD/SystemPackages/DefaultPicmanFigure/include
