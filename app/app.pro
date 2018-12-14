#-------------------------------------------------
#
# Project created by QtCreator 2018-12-07T21:40:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BathymetryViewer
TEMPLATE = app

win32-msvc* {
    QMAKE_CXXFLAGS += /Ot /GF /Oi /arch:AVX2 /permissive-
}

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++1z

DESTDIR = $$PWD/../build

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    openglwidget.cpp \
    inputmanager.cpp \
    resourcemanager.cpp \
    camera.cpp \
    timer.cpp \
    dialogsavescreenshot.cpp \
    transform3d.cpp \
    shader.cpp \
    gpuprogram.cpp \
    dialogpreferences.cpp

HEADERS += \
        mainwindow.h \
    openglwidget.h \
    inputmanager.h \
    resourcemanager.h \
    camera.h \
    timer.h \
    dialogsavescreenshot.h \
    vertex.h \
    transform3d.h \
    shader.h \
    gpuprogram.h \
    dialogpreferences.h

FORMS += \
        mainwindow.ui \
    dialogsavescreenshot.ui \
    dialogpreferences.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc \
    shaders.qrc
