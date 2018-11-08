/********************************************************************************
** Form generated from reading UI file 'atrparam.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ATRPARAM_H
#define UI_ATRPARAM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_atrparam
{
public:
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QComboBox *comboBox;
    QLabel *label;
    QCheckBox *checkBox;
    QSpinBox *spinBox;
    QLabel *label_3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *atrparam)
    {
        if (atrparam->objectName().isEmpty())
            atrparam->setObjectName(QStringLiteral("atrparam"));
        atrparam->resize(275, 222);
        gridLayout = new QGridLayout(atrparam);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_2 = new QLabel(atrparam);
        label_2->setObjectName(QStringLiteral("label_2"));
        QFont font;
        font.setFamily(QStringLiteral("Times New Roman"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 0, 0, 1, 2);

        lineEdit = new QLineEdit(atrparam);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setFont(font);

        gridLayout->addWidget(lineEdit, 1, 0, 1, 2);

        comboBox = new QComboBox(atrparam);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setFont(font);

        gridLayout->addWidget(comboBox, 3, 0, 1, 2);

        label = new QLabel(atrparam);
        label->setObjectName(QStringLiteral("label"));
        label->setFont(font);

        gridLayout->addWidget(label, 4, 0, 1, 1);

        checkBox = new QCheckBox(atrparam);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        checkBox->setFont(font1);

        gridLayout->addWidget(checkBox, 5, 0, 1, 2);

        spinBox = new QSpinBox(atrparam);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setEnabled(false);
        spinBox->setFont(font);

        gridLayout->addWidget(spinBox, 4, 1, 1, 1);

        label_3 = new QLabel(atrparam);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_3, 2, 0, 1, 2);

        pushButton = new QPushButton(atrparam);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setFont(font1);

        gridLayout->addWidget(pushButton, 6, 0, 1, 1);

        pushButton_2 = new QPushButton(atrparam);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setFont(font);

        gridLayout->addWidget(pushButton_2, 6, 1, 1, 1);

        QWidget::setTabOrder(lineEdit, comboBox);
        QWidget::setTabOrder(comboBox, spinBox);
        QWidget::setTabOrder(spinBox, checkBox);
        QWidget::setTabOrder(checkBox, pushButton);
        QWidget::setTabOrder(pushButton, pushButton_2);

        retranslateUi(atrparam);

        QMetaObject::connectSlotsByName(atrparam);
    } // setupUi

    void retranslateUi(QDialog *atrparam)
    {
        atrparam->setWindowTitle(QApplication::translate("atrparam", "Dialog", nullptr));
        label_2->setText(QApplication::translate("atrparam", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \320\260\321\202\321\200\320\270\320\261\321\203\321\202\320\260", nullptr));
        label->setText(QApplication::translate("atrparam", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \321\201\320\270\320\274\320\262\320\276\320\273\320\276\320\262", nullptr));
        checkBox->setText(QApplication::translate("atrparam", "\320\237\320\265\321\200\320\262\320\270\321\207\320\275\321\213\320\271 \320\272\320\273\321\216\321\207", nullptr));
        label_3->setText(QApplication::translate("atrparam", "\320\242\320\270\320\277 \320\264\320\260\320\275\320\275\321\213\321\205 \320\260\321\202\321\200\320\270\320\261\321\203\321\202\320\260", nullptr));
        pushButton->setText(QApplication::translate("atrparam", "\320\237\320\276\320\264\321\202\320\262\320\265\321\200\320\264\320\270\321\202\321\214", nullptr));
        pushButton_2->setText(QApplication::translate("atrparam", "\320\236\321\202\320\274\320\265\320\275\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class atrparam: public Ui_atrparam {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ATRPARAM_H
