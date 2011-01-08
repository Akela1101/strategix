/********************************************************************************
** Form generated from reading UI file 'MainForm.ui'
**
** Created: Wed Jan 5 19:01:55 2011
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINFORM_H
#define UI_MAINFORM_H

#include <MapArea.h>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QScrollArea>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainForm
{
public:
    QAction *actionNew;
    QAction *actionLoad;
    QAction *actionSave;
    QAction *actionExit;
    QAction *actionAbout;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QToolBox *toolBox;
    QWidget *page_0;
    QVBoxLayout *verticalLayout_3;
    QListWidget *toolsListWidget;
    QWidget *page_1;
    QVBoxLayout *verticalLayout;
    QListWidget *terrainListWidget;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_2;
    QListWidget *resourceListWidget;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_2;
    QGridLayout *gridLayout;
    MapArea *mapArea;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainForm)
    {
        if (MainForm->objectName().isEmpty())
            MainForm->setObjectName(QString::fromUtf8("MainForm"));
        MainForm->resize(927, 596);
        actionNew = new QAction(MainForm);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        actionLoad = new QAction(MainForm);
        actionLoad->setObjectName(QString::fromUtf8("actionLoad"));
        actionSave = new QAction(MainForm);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionExit = new QAction(MainForm);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionAbout = new QAction(MainForm);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        centralwidget = new QWidget(MainForm);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        toolBox = new QToolBox(centralwidget);
        toolBox->setObjectName(QString::fromUtf8("toolBox"));
        toolBox->setMinimumSize(QSize(300, 0));
        toolBox->setMaximumSize(QSize(300, 16777215));
        page_0 = new QWidget();
        page_0->setObjectName(QString::fromUtf8("page_0"));
        page_0->setGeometry(QRect(0, 0, 290, 451));
        verticalLayout_3 = new QVBoxLayout(page_0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        toolsListWidget = new QListWidget(page_0);
        toolsListWidget->setObjectName(QString::fromUtf8("toolsListWidget"));

        verticalLayout_3->addWidget(toolsListWidget);

        toolBox->addItem(page_0, QString::fromUtf8("Tools"));
        page_1 = new QWidget();
        page_1->setObjectName(QString::fromUtf8("page_1"));
        page_1->setGeometry(QRect(0, 0, 290, 451));
        verticalLayout = new QVBoxLayout(page_1);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        terrainListWidget = new QListWidget(page_1);
        terrainListWidget->setObjectName(QString::fromUtf8("terrainListWidget"));

        verticalLayout->addWidget(terrainListWidget);

        toolBox->addItem(page_1, QString::fromUtf8("Terrains"));
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        page_2->setGeometry(QRect(0, 0, 290, 451));
        verticalLayout_2 = new QVBoxLayout(page_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        resourceListWidget = new QListWidget(page_2);
        resourceListWidget->setObjectName(QString::fromUtf8("resourceListWidget"));

        verticalLayout_2->addWidget(resourceListWidget);

        toolBox->addItem(page_2, QString::fromUtf8("Resources"));

        horizontalLayout_2->addWidget(toolBox);

        scrollArea = new QScrollArea(centralwidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 609, 539));
        gridLayout = new QGridLayout(scrollAreaWidgetContents_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        mapArea = new MapArea(scrollAreaWidgetContents_2);
        mapArea->setObjectName(QString::fromUtf8("mapArea"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mapArea->sizePolicy().hasHeightForWidth());
        mapArea->setSizePolicy(sizePolicy);
        mapArea->setMinimumSize(QSize(300, 300));

        gridLayout->addWidget(mapArea, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents_2);

        horizontalLayout_2->addWidget(scrollArea);

        MainForm->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainForm);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 927, 22));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainForm->setMenuBar(menubar);
        statusbar = new QStatusBar(MainForm);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainForm->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addSeparator();
        menuFile->addAction(actionLoad);
        menuFile->addAction(actionSave);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuHelp->addAction(actionAbout);

        retranslateUi(MainForm);
        QObject::connect(actionNew, SIGNAL(triggered()), MainForm, SLOT(FileNew()));
        QObject::connect(terrainListWidget, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), MainForm, SLOT(CurrentItemChanged(QListWidgetItem*,QListWidgetItem*)));
        QObject::connect(resourceListWidget, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), MainForm, SLOT(CurrentItemChanged(QListWidgetItem*,QListWidgetItem*)));
        QObject::connect(toolBox, SIGNAL(currentChanged(int)), MainForm, SLOT(CurrentToolboxItemChanged(int)));
        QObject::connect(actionSave, SIGNAL(triggered()), MainForm, SLOT(FileSave()));
        QObject::connect(actionLoad, SIGNAL(triggered()), MainForm, SLOT(FileLoad()));
        QObject::connect(actionExit, SIGNAL(triggered()), MainForm, SLOT(close()));
        QObject::connect(actionAbout, SIGNAL(triggered()), MainForm, SLOT(HelpAbout()));
        QObject::connect(toolsListWidget, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), MainForm, SLOT(CurrentItemChanged(QListWidgetItem*,QListWidgetItem*)));

        toolBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainForm);
    } // setupUi

    void retranslateUi(QMainWindow *MainForm)
    {
        MainForm->setWindowTitle(QApplication::translate("MainForm", "Nyaaaaaaa!!!!!!!!!!!", 0, QApplication::UnicodeUTF8));
        actionNew->setText(QApplication::translate("MainForm", "New", 0, QApplication::UnicodeUTF8));
        actionNew->setShortcut(QApplication::translate("MainForm", "Ctrl+N", 0, QApplication::UnicodeUTF8));
        actionLoad->setText(QApplication::translate("MainForm", "Load", 0, QApplication::UnicodeUTF8));
        actionLoad->setShortcut(QApplication::translate("MainForm", "Ctrl+L", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("MainForm", "Save", 0, QApplication::UnicodeUTF8));
        actionSave->setShortcut(QApplication::translate("MainForm", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("MainForm", "Exit", 0, QApplication::UnicodeUTF8));
        actionExit->setShortcut(QApplication::translate("MainForm", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("MainForm", "About", 0, QApplication::UnicodeUTF8));
        toolBox->setItemText(toolBox->indexOf(page_0), QApplication::translate("MainForm", "Tools", 0, QApplication::UnicodeUTF8));
        toolBox->setItemText(toolBox->indexOf(page_1), QApplication::translate("MainForm", "Terrains", 0, QApplication::UnicodeUTF8));
        toolBox->setItemText(toolBox->indexOf(page_2), QApplication::translate("MainForm", "Resources", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainForm", "File", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("MainForm", "Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainForm: public Ui_MainForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFORM_H
