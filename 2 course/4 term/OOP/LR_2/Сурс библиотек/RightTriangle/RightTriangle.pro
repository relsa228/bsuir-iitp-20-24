QT += widgets

TEMPLATE = lib
DEFINES += RIGHTTRIANGLE_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    righttriangle.cpp

HEADERS += \
    RightTriangle_global.h \
    righttriangle.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

win32: LIBS += -L$$PWD/../git/OOP-Cpp/LR_2/Paint/SystemPackages/DefaultPicmanFigure/lib/ -lDefaultPicManFigure

INCLUDEPATH += $$PWD/../git/OOP-Cpp/LR_2/Paint/SystemPackages/DefaultPicmanFigure/include
DEPENDPATH += $$PWD/../git/OOP-Cpp/LR_2/Paint/SystemPackages/DefaultPicmanFigure/include
