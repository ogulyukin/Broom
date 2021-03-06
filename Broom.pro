QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = app
win32 : RC_ICONS += Broom.ico
CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    configloader.cpp \
    dirinfo.cpp \
    logger.cpp \
    main.cpp \
    mainwindow.cpp \
    task1c.cpp \
    taskmozilla.cpp \
    taskobject.cpp \
    taskthread.cpp \
    tasktrashbox.cpp \
    taskuserpath.cpp

HEADERS += \
    configloader.h \
    dirinfo.h \
    logger.h \
    mainwindow.h \
    task1c.h \
    taskmozilla.h \
    taskobject.h \
    taskthread.h \
    tasktrashbox.h \
    taskuserpath.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    broom.qrc
