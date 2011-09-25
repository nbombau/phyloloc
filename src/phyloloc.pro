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
    PhyloGUI/src/filedialog.cpp \
    PhyloGUI/src/propagatedialog.cpp \
    PhyloGUI/src/nodedetaildialog.cpp \
    Phylopp/Consensor/bitset.cpp \
    Phylopp/Consensor/StrictConsensor.cpp \
    Phyloloc/Propagator/StatisticCollector.cpp

HEADERS  += PhyloGUI/inc/mainwindow.h \
    PhyloGUI/inc/graphwidget.h \
    PhyloGUI/inc/edge.h \
    PhyloGUI/GuiAspect.h \
    Domain/INode.h \
    PhyloGUI/inc/filedialog.h \
    PhyloGUI/inc/propagatedialog.h \
    PhyloGUI/inc/nodedetaildialog.h \
    Phylopp/Consensor/bitset.h \
    Phylopp/Consensor/StrictConsensor.h \
    Phylopp/Consensor/MacroConsensorObserver.h \
    Phylopp/Consensor/IConsensorStrategy.h \
    Phylopp/Consensor/IConsensorObserver.h \
    Phylopp/Consensor/IConsensorFactory.h \
    Phylopp/Consensor/ConsensorAspect.h \
    Phylopp/Consensor/ClusterTree.h \
    Phyloloc/Propagator/VectorHelper.h \
    Phyloloc/Propagator/TraversalPredicates.h \
    Phyloloc/Propagator/StatisticStrictConsensor.h \
    Phyloloc/Propagator/StatisticsAspect.h \
    Phyloloc/Propagator/StatisticLoadAction.h \
    Phyloloc/Propagator/StatisticInfo.h \
    Phyloloc/Propagator/StatisticCollectorObserver.h \
    Phyloloc/Propagator/StatisticCollector.h \
    Phyloloc/Propagator/PropagatorAspect.h \
    Phyloloc/Propagator/PropagatorAction.h \
    Phyloloc/Propagator/Propagator.h

FORMS    += PhyloGUI/forms/mainwindow.ui

QMAKE_CXXFLAGS += -pedantic -Wextra -ansi -Wno-long-long -ggdb3

OTHER_FILES += \
    Phylopp/Consensor/StatisticConsensorObserverTest
