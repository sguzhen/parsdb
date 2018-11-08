/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action;
    QAction *action_2;
    QAction *action_MS_SQL_Server_2;
    QAction *closeApp;
    QAction *action_MS_SQL_Server;
    QAction *vigrDB;
    QAction *action_6;
    QAction *action_3;
    QAction *action_SaveScheme;
    QAction *action_LoadScheme;
    QAction *SimpleSave;
    QAction *checkUpdate;
    QAction *netWork;
    QAction *addRemChat;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit;
    QGraphicsView *graphicsView;
    QPlainTextEdit *plainTextEdit;
    QPushButton *pushButton;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_5;
    QMenu *menu_3;
    QMenu *menu_4;
    QMenu *menu_2;
    QMenu *menu_6;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(843, 514);
        MainWindow->setMinimumSize(QSize(566, 400));
        action = new QAction(MainWindow);
        action->setObjectName(QStringLiteral("action"));
        action_2 = new QAction(MainWindow);
        action_2->setObjectName(QStringLiteral("action_2"));
        action_MS_SQL_Server_2 = new QAction(MainWindow);
        action_MS_SQL_Server_2->setObjectName(QStringLiteral("action_MS_SQL_Server_2"));
        closeApp = new QAction(MainWindow);
        closeApp->setObjectName(QStringLiteral("closeApp"));
        action_MS_SQL_Server = new QAction(MainWindow);
        action_MS_SQL_Server->setObjectName(QStringLiteral("action_MS_SQL_Server"));
        action_MS_SQL_Server->setEnabled(false);
        vigrDB = new QAction(MainWindow);
        vigrDB->setObjectName(QStringLiteral("vigrDB"));
        vigrDB->setEnabled(false);
        action_6 = new QAction(MainWindow);
        action_6->setObjectName(QStringLiteral("action_6"));
        action_3 = new QAction(MainWindow);
        action_3->setObjectName(QStringLiteral("action_3"));
        action_SaveScheme = new QAction(MainWindow);
        action_SaveScheme->setObjectName(QStringLiteral("action_SaveScheme"));
        action_SaveScheme->setEnabled(true);
        action_LoadScheme = new QAction(MainWindow);
        action_LoadScheme->setObjectName(QStringLiteral("action_LoadScheme"));
        SimpleSave = new QAction(MainWindow);
        SimpleSave->setObjectName(QStringLiteral("SimpleSave"));
        SimpleSave->setEnabled(false);
        checkUpdate = new QAction(MainWindow);
        checkUpdate->setObjectName(QStringLiteral("checkUpdate"));
        netWork = new QAction(MainWindow);
        netWork->setObjectName(QStringLiteral("netWork"));
        netWork->setCheckable(true);
        addRemChat = new QAction(MainWindow);
        addRemChat->setObjectName(QStringLiteral("addRemChat"));
        addRemChat->setCheckable(true);
        addRemChat->setEnabled(false);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(lineEdit, 2, 1, 1, 1);

        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setEnabled(true);
        graphicsView->setAutoFillBackground(false);
        graphicsView->setInteractive(true);
        graphicsView->setTransformationAnchor(QGraphicsView::AnchorViewCenter);

        gridLayout->addWidget(graphicsView, 1, 0, 3, 1);

        plainTextEdit = new QPlainTextEdit(centralWidget);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->setMaximumSize(QSize(150, 16777215));
        plainTextEdit->setFrameShadow(QFrame::Sunken);
        plainTextEdit->setReadOnly(true);

        gridLayout->addWidget(plainTextEdit, 1, 1, 1, 1);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 3, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 843, 21));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        QFont font;
        font.setFamily(QStringLiteral("Tahoma"));
        menu->setFont(font);
        menu_5 = new QMenu(menu);
        menu_5->setObjectName(QStringLiteral("menu_5"));
        menu_3 = new QMenu(menuBar);
        menu_3->setObjectName(QStringLiteral("menu_3"));
        menu_4 = new QMenu(menuBar);
        menu_4->setObjectName(QStringLiteral("menu_4"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        menu_6 = new QMenu(menuBar);
        menu_6->setObjectName(QStringLiteral("menu_6"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_3->menuAction());
        menuBar->addAction(menu_4->menuAction());
        menuBar->addAction(menu_6->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menu->addAction(action_6);
        menu->addSeparator();
        menu->addAction(menu_5->menuAction());
        menu->addAction(SimpleSave);
        menu->addAction(action_SaveScheme);
        menu->addAction(action_LoadScheme);
        menu->addAction(closeApp);
        menu_5->addAction(action_MS_SQL_Server_2);
        menu_5->addAction(vigrDB);
        menu_5->addAction(action_MS_SQL_Server);
        menu_3->addAction(action);
        menu_4->addAction(action_2);
        menu_2->addAction(checkUpdate);
        menu_2->addAction(action_3);
        menu_6->addAction(netWork);
        menu_6->addAction(addRemChat);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        action->setText(QApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\201\321\203\321\211\320\275\320\276\321\201\321\202\321\214", nullptr));
        action_2->setText(QApplication::translate("MainWindow", "\320\241\321\204\320\276\321\200\320\274\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\272\320\276\320\264", nullptr));
        action_MS_SQL_Server_2->setText(QApplication::translate("MainWindow", "\320\241\320\276\320\265\320\264\320\270\320\275\320\270\321\202\321\214\321\201\321\217 \321\201 MS SQL Server", nullptr));
        closeApp->setText(QApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264", nullptr));
        action_MS_SQL_Server->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\272\320\273\321\216\321\207\320\270\321\202\321\214\321\201\321\217 \320\276\321\202 MS SQL Server", nullptr));
        vigrDB->setText(QApplication::translate("MainWindow", "\320\222\321\213\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \321\201\321\202\321\200\321\203\320\272\321\202\321\203\321\200\321\203 \320\270\320\267 \320\221\320\224", nullptr));
        action_6->setText(QApplication::translate("MainWindow", "\320\235\320\276\320\262\321\213\320\271 \320\273\320\270\321\201\321\202", nullptr));
        action_3->setText(QApplication::translate("MainWindow", "\320\236 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\265...", nullptr));
        action_SaveScheme->setText(QApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \321\201\321\205\320\265\320\274\321\203 \320\272\320\260\320\272...", nullptr));
        action_LoadScheme->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \321\201\321\205\320\265\320\274\321\203", nullptr));
        SimpleSave->setText(QApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        checkUpdate->setText(QApplication::translate("MainWindow", "\320\237\321\200\320\276\320\262\320\265\321\200\320\270\321\202\321\214 \320\276\320\261\320\275\320\276\320\262\320\273\320\265\320\275\320\270\320\265", nullptr));
        netWork->setText(QApplication::translate("MainWindow", "\320\241\320\265\321\202\320\265\320\262\320\276\320\271 \321\200\320\265\320\266\320\270\320\274 \320\262\320\272\320\273/\320\262\321\213\320\272\320\273", nullptr));
        addRemChat->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\272\320\260\320\267\320\260\321\202\321\214/\321\201\320\272\321\200\321\213\321\202\321\214 \321\207\320\260\321\202", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214 \321\201\320\276\320\276\320\261\321\211\320\265\320\275\320\270\320\265", nullptr));
        menu->setTitle(QApplication::translate("MainWindow", "\320\244\320\260\320\271\320\273", nullptr));
        menu_5->setTitle(QApplication::translate("MainWindow", "\320\236\320\277\320\265\321\200\320\260\321\206\320\270\320\270 \321\201 \320\221\320\224", nullptr));
        menu_3->setTitle(QApplication::translate("MainWindow", "\320\241\321\203\321\211\320\275\320\276\321\201\321\202\321\214", nullptr));
        menu_4->setTitle(QApplication::translate("MainWindow", "\320\232\320\276\320\264", nullptr));
        menu_2->setTitle(QApplication::translate("MainWindow", "\320\241\320\277\321\200\320\260\320\262\320\272\320\260", nullptr));
        menu_6->setTitle(QApplication::translate("MainWindow", "\320\241\320\265\321\202\320\265\320\262\320\260\321\217 \321\200\320\260\320\261\320\276\321\202\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
