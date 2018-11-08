/********************************************************************************
** Form generated from reading UI file 'suzhparam.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUZHPARAM_H
#define UI_SUZHPARAM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_suzhparam
{
public:
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QLineEdit *lineEdit;

    void setupUi(QWidget *suzhparam)
    {
        if (suzhparam->objectName().isEmpty())
            suzhparam->setObjectName(QStringLiteral("suzhparam"));
        suzhparam->resize(269, 78);
        gridLayout = new QGridLayout(suzhparam);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pushButton = new QPushButton(suzhparam);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        pushButton->setFont(font);

        gridLayout->addWidget(pushButton, 1, 0, 1, 1);

        lineEdit = new QLineEdit(suzhparam);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setFont(font);

        gridLayout->addWidget(lineEdit, 0, 0, 1, 1);

        QWidget::setTabOrder(lineEdit, pushButton);

        retranslateUi(suzhparam);

        QMetaObject::connectSlotsByName(suzhparam);
    } // setupUi

    void retranslateUi(QWidget *suzhparam)
    {
        suzhparam->setWindowTitle(QApplication::translate("suzhparam", "Form", nullptr));
        pushButton->setText(QApplication::translate("suzhparam", "\320\243\321\202\320\262\320\265\321\200\320\264\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class suzhparam: public Ui_suzhparam {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUZHPARAM_H
