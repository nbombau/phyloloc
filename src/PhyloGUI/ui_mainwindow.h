/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sat Apr 30 17:42:54 2011
**      by: Qt User Interface Compiler version 4.7.0
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
#include <QtGui/QMdiArea>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionSave_As;
    QAction *actionQuit;
    QAction *actionProcess_tree;
    QAction *actionConcense_trees;
    QAction *actionParameters;
    QAction *actionOptions;
    QAction *actionClear_selection;
    QAction *actionSelect_descendants;
    QAction *actionSelect_Ancestors;
    QAction *actionExpand;
    QAction *actionCollapse;
    QAction *actionColor_nodes;
    QAction *actionNode_details;
    QAction *actionSelect_all_nodes;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QListWidget *listWidget;
    QMdiArea *frame;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuNode;
    QMenu *menuTools;
    QMenu *menuConfiguration;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
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
        actionParameters = new QAction(MainWindow);
        actionParameters->setObjectName(QString::fromUtf8("actionParameters"));
        actionOptions = new QAction(MainWindow);
        actionOptions->setObjectName(QString::fromUtf8("actionOptions"));
        actionClear_selection = new QAction(MainWindow);
        actionClear_selection->setObjectName(QString::fromUtf8("actionClear_selection"));
        actionSelect_descendants = new QAction(MainWindow);
        actionSelect_descendants->setObjectName(QString::fromUtf8("actionSelect_descendants"));
        actionSelect_Ancestors = new QAction(MainWindow);
        actionSelect_Ancestors->setObjectName(QString::fromUtf8("actionSelect_Ancestors"));
        actionExpand = new QAction(MainWindow);
        actionExpand->setObjectName(QString::fromUtf8("actionExpand"));
        actionCollapse = new QAction(MainWindow);
        actionCollapse->setObjectName(QString::fromUtf8("actionCollapse"));
        actionColor_nodes = new QAction(MainWindow);
        actionColor_nodes->setObjectName(QString::fromUtf8("actionColor_nodes"));
        actionNode_details = new QAction(MainWindow);
        actionNode_details->setObjectName(QString::fromUtf8("actionNode_details"));
        actionSelect_all_nodes = new QAction(MainWindow);
        actionSelect_all_nodes->setObjectName(QString::fromUtf8("actionSelect_all_nodes"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setMinimumSize(QSize(101, 271));
        listWidget->setMaximumSize(QSize(141, 16777215));

        horizontalLayout->addWidget(listWidget);

        frame = new QMdiArea(centralWidget);
        frame->setObjectName(QString::fromUtf8("frame"));

        horizontalLayout->addWidget(frame);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 640, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuNode = new QMenu(menuBar);
        menuNode->setObjectName(QString::fromUtf8("menuNode"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QString::fromUtf8("menuTools"));
        menuConfiguration = new QMenu(menuBar);
        menuConfiguration->setObjectName(QString::fromUtf8("menuConfiguration"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuNode->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuBar->addAction(menuConfiguration->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave_As);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);
        menuNode->addAction(actionClear_selection);
        menuNode->addAction(actionSelect_descendants);
        menuNode->addAction(actionSelect_Ancestors);
        menuNode->addAction(actionExpand);
        menuNode->addAction(actionCollapse);
        menuNode->addAction(actionColor_nodes);
        menuNode->addAction(actionSelect_all_nodes);
        menuTools->addAction(actionProcess_tree);
        menuTools->addAction(actionConcense_trees);
        menuConfiguration->addAction(actionParameters);
        menuConfiguration->addAction(actionOptions);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
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
        actionProcess_tree->setText(QApplication::translate("MainWindow", "Process trees...", 0, QApplication::UnicodeUTF8));
        actionConcense_trees->setText(QApplication::translate("MainWindow", "Concense trees...", 0, QApplication::UnicodeUTF8));
        actionParameters->setText(QApplication::translate("MainWindow", "Parameters...", 0, QApplication::UnicodeUTF8));
        actionOptions->setText(QApplication::translate("MainWindow", "Options...", 0, QApplication::UnicodeUTF8));
        actionOptions->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+O", 0, QApplication::UnicodeUTF8));
        actionClear_selection->setText(QApplication::translate("MainWindow", "Clear selection", 0, QApplication::UnicodeUTF8));
        actionSelect_descendants->setText(QApplication::translate("MainWindow", "Select descendants", 0, QApplication::UnicodeUTF8));
        actionSelect_Ancestors->setText(QApplication::translate("MainWindow", "Select ancestors", 0, QApplication::UnicodeUTF8));
        actionExpand->setText(QApplication::translate("MainWindow", "Expand (not working)", 0, QApplication::UnicodeUTF8));
        actionCollapse->setText(QApplication::translate("MainWindow", "Collapse (not working)", 0, QApplication::UnicodeUTF8));
        actionColor_nodes->setText(QApplication::translate("MainWindow", "Color nodes...", 0, QApplication::UnicodeUTF8));
        actionNode_details->setText(QApplication::translate("MainWindow", "Node details...", 0, QApplication::UnicodeUTF8));
        actionSelect_all_nodes->setText(QApplication::translate("MainWindow", "Select all nodes", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        menuNode->setTitle(QApplication::translate("MainWindow", "Node", 0, QApplication::UnicodeUTF8));
        menuTools->setTitle(QApplication::translate("MainWindow", "Tools", 0, QApplication::UnicodeUTF8));
        menuConfiguration->setTitle(QApplication::translate("MainWindow", "Configuration", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
