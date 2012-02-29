/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Mon Feb 20 17:52:19 2012
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QSplitter>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction* actionOpen;
    QAction* actionSave_As;
    QAction* actionQuit;
    QAction* actionProcess_tree;
    QAction* actionConcense_trees;
    QAction* actionClear_selection;
    QAction* actionSelect_descendants;
    QAction* actionSelect_Ancestors;
    QAction* actionColor_nodes;
    QAction* actionSelect_all_nodes;
    QAction* actionSearch_terminal_nodes;
    QAction* actionZoom;
    QAction* actionZoom_2;
    QAction* actionActual_size;
    QAction* actionClose_all;
    QAction* actionAbout;
    QAction* actionClear_nodes_color;
    QWidget* centralWidget;
    QHBoxLayout* horizontalLayout;
    QSplitter* splitter;
    QListWidget* listWidget;
    QMenuBar* menuBar;
    QMenu* menuFile;
    QMenu* menuNode;
    QMenu* menuTools;
    QMenu* menuView;
    QMenu* menuHelp;
    QToolBar* mainToolBar;
    QStatusBar* statusBar;

    void setupUi(QMainWindow* MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(640, 351);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionSave_As = new QAction(MainWindow);
        actionSave_As->setObjectName(QString::fromUtf8("actionSave_As"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionProcess_tree = new QAction(MainWindow);
        actionProcess_tree->setObjectName(QString::fromUtf8("actionProcess_tree"));
        actionConcense_trees = new QAction(MainWindow);
        actionConcense_trees->setObjectName(QString::fromUtf8("actionConcense_trees"));
        actionClear_selection = new QAction(MainWindow);
        actionClear_selection->setObjectName(QString::fromUtf8("actionClear_selection"));
        actionSelect_descendants = new QAction(MainWindow);
        actionSelect_descendants->setObjectName(QString::fromUtf8("actionSelect_descendants"));
        actionSelect_Ancestors = new QAction(MainWindow);
        actionSelect_Ancestors->setObjectName(QString::fromUtf8("actionSelect_Ancestors"));
        actionColor_nodes = new QAction(MainWindow);
        actionColor_nodes->setObjectName(QString::fromUtf8("actionColor_nodes"));
        actionSelect_all_nodes = new QAction(MainWindow);
        actionSelect_all_nodes->setObjectName(QString::fromUtf8("actionSelect_all_nodes"));
        actionSearch_terminal_nodes = new QAction(MainWindow);
        actionSearch_terminal_nodes->setObjectName(QString::fromUtf8("actionSearch_terminal_nodes"));
        actionZoom = new QAction(MainWindow);
        actionZoom->setObjectName(QString::fromUtf8("actionZoom"));
        actionZoom_2 = new QAction(MainWindow);
        actionZoom_2->setObjectName(QString::fromUtf8("actionZoom_2"));
        actionActual_size = new QAction(MainWindow);
        actionActual_size->setObjectName(QString::fromUtf8("actionActual_size"));
        actionClose_all = new QAction(MainWindow);
        actionClose_all->setObjectName(QString::fromUtf8("actionClose_all"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionClear_nodes_color = new QAction(MainWindow);
        actionClear_nodes_color->setObjectName(QString::fromUtf8("actionClear_nodes_color"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        listWidget = new QListWidget(splitter);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setMinimumSize(QSize(101, 271));
        listWidget->setMaximumSize(QSize(1410, 16777215));
        splitter->addWidget(listWidget);

        horizontalLayout->addWidget(splitter);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 640, 23));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuNode = new QMenu(menuBar);
        menuNode->setObjectName(QString::fromUtf8("menuNode"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QString::fromUtf8("menuTools"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuNode->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave_As);
        menuFile->addSeparator();
        menuFile->addAction(actionClose_all);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);
        menuNode->addAction(actionSelect_all_nodes);
        menuNode->addAction(actionClear_selection);
        menuNode->addAction(actionSelect_descendants);
        menuNode->addAction(actionSelect_Ancestors);
        menuNode->addSeparator();
        menuNode->addAction(actionColor_nodes);
        menuNode->addAction(actionClear_nodes_color);
        menuNode->addSeparator();
        menuNode->addAction(actionSearch_terminal_nodes);
        menuTools->addAction(actionProcess_tree);
        menuView->addAction(actionZoom);
        menuView->addAction(actionZoom_2);
        menuView->addSeparator();
        menuView->addAction(actionActual_size);
        menuHelp->addAction(actionAbout);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow* MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Phyloloc", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("MainWindow", "Open...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionOpen->setToolTip(QApplication::translate("MainWindow", "Open a new file", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionOpen->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        actionSave_As->setText(QApplication::translate("MainWindow", "Save As...", 0, QApplication::UnicodeUTF8));
        actionSave_As->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionQuit->setToolTip(QApplication::translate("MainWindow", "Quit the application", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionQuit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        actionProcess_tree->setText(QApplication::translate("MainWindow", "Propagate...", 0, QApplication::UnicodeUTF8));
        actionConcense_trees->setText(QApplication::translate("MainWindow", "Concense trees...", 0, QApplication::UnicodeUTF8));
        actionClear_selection->setText(QApplication::translate("MainWindow", "Clear selection", 0, QApplication::UnicodeUTF8));
        actionSelect_descendants->setText(QApplication::translate("MainWindow", "Select descendants", 0, QApplication::UnicodeUTF8));
        actionSelect_Ancestors->setText(QApplication::translate("MainWindow", "Select ancestors", 0, QApplication::UnicodeUTF8));
        actionColor_nodes->setText(QApplication::translate("MainWindow", "Color nodes...", 0, QApplication::UnicodeUTF8));
        actionSelect_all_nodes->setText(QApplication::translate("MainWindow", "Select all nodes", 0, QApplication::UnicodeUTF8));
        actionSelect_all_nodes->setShortcut(QApplication::translate("MainWindow", "Ctrl+A", 0, QApplication::UnicodeUTF8));
        actionSearch_terminal_nodes->setText(QApplication::translate("MainWindow", "Search terminal nodes...", 0, QApplication::UnicodeUTF8));
        actionSearch_terminal_nodes->setShortcut(QApplication::translate("MainWindow", "Ctrl+F", 0, QApplication::UnicodeUTF8));
        actionZoom->setText(QApplication::translate("MainWindow", "Zoom +", 0, QApplication::UnicodeUTF8));
        actionZoom->setShortcut(QApplication::translate("MainWindow", "Ctrl++", 0, QApplication::UnicodeUTF8));
        actionZoom_2->setText(QApplication::translate("MainWindow", "Zoom -", 0, QApplication::UnicodeUTF8));
        actionZoom_2->setShortcut(QApplication::translate("MainWindow", "Ctrl+-", 0, QApplication::UnicodeUTF8));
        actionActual_size->setText(QApplication::translate("MainWindow", "Actual size", 0, QApplication::UnicodeUTF8));
        actionActual_size->setShortcut(QApplication::translate("MainWindow", "Ctrl+0", 0, QApplication::UnicodeUTF8));
        actionClose_all->setText(QApplication::translate("MainWindow", "Close all...", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0, QApplication::UnicodeUTF8));
        actionClear_nodes_color->setText(QApplication::translate("MainWindow", "Clear nodes color", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
        menuNode->setTitle(QApplication::translate("MainWindow", "&Node", 0, QApplication::UnicodeUTF8));
        menuTools->setTitle(QApplication::translate("MainWindow", "&Tools", 0, QApplication::UnicodeUTF8));
        menuView->setTitle(QApplication::translate("MainWindow", "&View", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("MainWindow", "&Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui
{
class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
