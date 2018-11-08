/********************************************************************************
** Form generated from reading UI file 'setsvyaz.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETSVYAZ_H
#define UI_SETSVYAZ_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_setSvyaz
{
public:
    QGridLayout *gridLayout;
    QComboBox *comboBox;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QListWidget *listWidget;
    QListWidget *listWidget_2;
    QLabel *label_2;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;

    void setupUi(QDialog *setSvyaz)
    {
        if (setSvyaz->objectName().isEmpty())
            setSvyaz->setObjectName(QStringLiteral("setSvyaz"));
        setSvyaz->resize(547, 342);
        gridLayout = new QGridLayout(setSvyaz);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        comboBox = new QComboBox(setSvyaz);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        QFont font;
        font.setFamily(QStringLiteral("Times New Roman"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        comboBox->setFont(font);
        comboBox->setSizeAdjustPolicy(QComboBox::AdjustToContentsOnFirstShow);

        gridLayout->addWidget(comboBox, 4, 0, 1, 1);

        lineEdit = new QLineEdit(setSvyaz);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setFont(font);

        gridLayout->addWidget(lineEdit, 4, 1, 1, 1);

        pushButton = new QPushButton(setSvyaz);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 5, 0, 1, 2);

        listWidget = new QListWidget(setSvyaz);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        gridLayout->addWidget(listWidget, 2, 0, 1, 1);

        listWidget_2 = new QListWidget(setSvyaz);
        listWidget_2->setObjectName(QStringLiteral("listWidget_2"));

        gridLayout->addWidget(listWidget_2, 2, 1, 1, 1);

        label_2 = new QLabel(setSvyaz);
        label_2->setObjectName(QStringLiteral("label_2"));
        QFont font1;
        font1.setFamily(QStringLiteral("Times New Roman"));
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 3, 1, 1, 1);

        label = new QLabel(setSvyaz);
        label->setObjectName(QStringLiteral("label"));
        label->setFont(font1);
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 3, 0, 1, 1);

        label_3 = new QLabel(setSvyaz);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_3, 0, 0, 1, 2);

        label_4 = new QLabel(setSvyaz);
        label_4->setObjectName(QStringLiteral("label_4"));
        QFont font2;
        font2.setBold(true);
        font2.setWeight(75);
        label_4->setFont(font2);
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        label_5 = new QLabel(setSvyaz);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font2);
        label_5->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_5, 1, 1, 1, 1);


        retranslateUi(setSvyaz);

        QMetaObject::connectSlotsByName(setSvyaz);
    } // setupUi

    void retranslateUi(QDialog *setSvyaz)
    {
        setSvyaz->setWindowTitle(QApplication::translate("setSvyaz", "Dialog", nullptr));
        pushButton->setText(QApplication::translate("setSvyaz", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214 \321\201\320\276\320\265\320\264\320\270\320\275\320\265\320\275\320\270\320\265", nullptr));
        label_2->setText(QApplication::translate("setSvyaz", "\320\236\320\277\320\270\321\201\320\260\320\275\320\270\320\265 \321\201\320\276\320\265\320\264\320\270\320\275\320\265\320\275\320\270\321\217", nullptr));
        label->setText(QApplication::translate("setSvyaz", "\320\241\321\202\320\265\320\277\320\265\320\275\321\214 \321\201\320\276\320\265\320\264\320\270\320\275\320\265\320\275\320\270\321\217", nullptr));
        label_3->setText(QApplication::translate("setSvyaz", "\320\235\320\265\320\276\320\261\321\205\320\276\320\264\320\270\320\274\320\276 \320\262\321\213\320\261\321\200\320\260\321\202\321\214 \320\264\320\262\320\265 \321\201\321\203\321\211\320\275\320\276\321\201\321\202\320\270 \320\264\320\273\321\217 \320\276\321\200\320\263\320\260\320\275\320\270\320\267\320\260\321\206\320\270\320\270 \321\201\320\262\321\217\320\267\320\270", nullptr));
        label_4->setText(QApplication::translate("setSvyaz", "\320\223\320\273\320\260\320\262\320\275\320\260\321\217 \321\201\321\203\321\211\320\275\320\276\321\201\321\202\321\214", nullptr));
        label_5->setText(QApplication::translate("setSvyaz", "\320\222\321\202\320\276\321\200\320\276\321\201\321\202\320\265\320\277\320\265\320\275\320\275\320\260\321\217 \321\201\321\203\321\211\320\275\320\276\321\201\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class setSvyaz: public Ui_setSvyaz {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETSVYAZ_H
