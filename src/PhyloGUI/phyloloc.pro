#-------------------------------------------------
#
# Project created by QtCreator 2011-04-04T23:13:18
#
#-------------------------------------------------

QT       += core gui

TARGET = phyloloc
TEMPLATE = app


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/graphwidget.cpp \
    src/edge.cpp \
    src/node.cpp

HEADERS  += inc/mainwindow.h \
    inc/graphwidget.h \
    inc/edge.h \
    inc/node.h \
    GuiAspect.h \
    ../Domain/INode.h

FORMS    += forms/mainwindow.ui
