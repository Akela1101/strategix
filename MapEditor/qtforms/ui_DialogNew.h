/********************************************************************************
** Form generated from reading UI file 'DialogNew.ui'
**
** Created: Wed Sep 29 20:26:43 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGNEW_H
#define UI_DIALOGNEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_DialogNew
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QLCDNumber *lcdNumber_2;
    QSlider *verticalSlider;
    QLCDNumber *lcdNumber;
    QSpacerItem *horizontalSpacer;
    QPushButton *cancelButton;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    QPushButton *createButton;
    QSlider *horizontalSlider;

    void setupUi(QDialog *DialogNew)
    {
        if (DialogNew->objectName().isEmpty())
            DialogNew->setObjectName(QString::fromUtf8("DialogNew"));
        DialogNew->resize(280, 332);
        gridLayout = new QGridLayout(DialogNew);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(DialogNew);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineEdit = new QLineEdit(DialogNew);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 1, 1, 2);

        lcdNumber_2 = new QLCDNumber(DialogNew);
        lcdNumber_2->setObjectName(QString::fromUtf8("lcdNumber_2"));
        lcdNumber_2->setFrameShape(QFrame::Panel);
        lcdNumber_2->setFrameShadow(QFrame::Raised);
        lcdNumber_2->setNumDigits(3);
        lcdNumber_2->setSegmentStyle(QLCDNumber::Outline);
        lcdNumber_2->setProperty("intValue", QVariant(15));

        gridLayout->addWidget(lcdNumber_2, 1, 2, 1, 1);

        verticalSlider = new QSlider(DialogNew);
        verticalSlider->setObjectName(QString::fromUtf8("verticalSlider"));
        verticalSlider->setMinimum(10);
        verticalSlider->setMaximum(100);
        verticalSlider->setSingleStep(10);
        verticalSlider->setValue(10);
        verticalSlider->setSliderPosition(10);
        verticalSlider->setOrientation(Qt::Vertical);
        verticalSlider->setTickPosition(QSlider::TicksBothSides);
        verticalSlider->setTickInterval(10);

        gridLayout->addWidget(verticalSlider, 2, 3, 1, 1);

        lcdNumber = new QLCDNumber(DialogNew);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setFrameShape(QFrame::Panel);
        lcdNumber->setFrameShadow(QFrame::Raised);
        lcdNumber->setNumDigits(3);
        lcdNumber->setSegmentStyle(QLCDNumber::Outline);
        lcdNumber->setProperty("intValue", QVariant(10));

        gridLayout->addWidget(lcdNumber, 3, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(175, 25, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 4, 1, 1, 1);

        cancelButton = new QPushButton(DialogNew);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        gridLayout->addWidget(cancelButton, 4, 2, 1, 2);

        frame = new QFrame(DialogNew);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setFrameShape(QFrame::Box);
        label_2->setPixmap(QPixmap(QString::fromUtf8("../../../../../media/SATA500/Pictures/APictures/Ha_5.gif")));
        label_2->setScaledContents(true);

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);


        gridLayout->addWidget(frame, 2, 0, 1, 3);

        createButton = new QPushButton(DialogNew);
        createButton->setObjectName(QString::fromUtf8("createButton"));

        gridLayout->addWidget(createButton, 4, 0, 1, 1);

        horizontalSlider = new QSlider(DialogNew);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setMinimum(10);
        horizontalSlider->setMaximum(100);
        horizontalSlider->setSingleStep(10);
        horizontalSlider->setValue(15);
        horizontalSlider->setSliderPosition(15);
        horizontalSlider->setTracking(false);
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider->setInvertedAppearance(false);
        horizontalSlider->setInvertedControls(false);
        horizontalSlider->setTickPosition(QSlider::TicksBothSides);
        horizontalSlider->setTickInterval(10);

        gridLayout->addWidget(horizontalSlider, 1, 0, 1, 2);


        retranslateUi(DialogNew);
        QObject::connect(verticalSlider, SIGNAL(valueChanged(int)), lcdNumber, SLOT(display(int)));
        QObject::connect(horizontalSlider, SIGNAL(valueChanged(int)), lcdNumber_2, SLOT(display(int)));
        QObject::connect(cancelButton, SIGNAL(clicked()), DialogNew, SLOT(reject()));
        QObject::connect(createButton, SIGNAL(clicked()), DialogNew, SLOT(accept()));

        QMetaObject::connectSlotsByName(DialogNew);
    } // setupUi

    void retranslateUi(QDialog *DialogNew)
    {
        DialogNew->setWindowTitle(QApplication::translate("DialogNew", "DialogNew", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("DialogNew", "Name", 0, QApplication::UnicodeUTF8));
        lineEdit->setText(QApplication::translate("DialogNew", "NewMap", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("DialogNew", "Cancel", 0, QApplication::UnicodeUTF8));
        label_2->setText(QString());
        createButton->setText(QApplication::translate("DialogNew", "Create", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DialogNew: public Ui_DialogNew {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGNEW_H
