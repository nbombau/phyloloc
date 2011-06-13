#-------------------------------------------------
#
# Project created by QtCreator 2011-04-04T23:13:18
#
#-------------------------------------------------

QT       += core gui

TARGET = phyloloc
TEMPLATE = app


SOURCES += PhyloGUI/src/main.cpp\
        PhyloGUI/src/mainwindow.cpp \
    PhyloGUI/src/graphwidget.cpp \
    PhyloGUI/src/edge.cpp \
    PhyloGUI/src/filedialog.cpp

HEADERS  += PhyloGUI/inc/mainwindow.h \
    PhyloGUI/inc/graphwidget.h \
    PhyloGUI/inc/edge.h \
    PhyloGUI/GuiAspect.h \
    Domain/INode.h \
    PhyloGUI/inc/filedialog.h

FORMS    += PhyloGUI/forms/mainwindow.ui
