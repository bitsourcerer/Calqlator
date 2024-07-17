/********************************************************************************
** Form generated from reading UI file 'prompt.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROMPT_H
#define UI_PROMPT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_Prompt
{
public:
    QDialogButtonBox *action;
    QLabel *purpose;
    QLineEdit *expression;

    void setupUi(QDialog *Prompt)
    {
        if (Prompt->objectName().isEmpty())
            Prompt->setObjectName("Prompt");
        Prompt->resize(515, 170);
        action = new QDialogButtonBox(Prompt);
        action->setObjectName("action");
        action->setGeometry(QRect(60, 120, 341, 32));
        action->setOrientation(Qt::Horizontal);
        action->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        purpose = new QLabel(Prompt);
        purpose->setObjectName("purpose");
        purpose->setGeometry(QRect(30, 10, 451, 31));
        QFont font;
        font.setFamilies({QString::fromUtf8("Padauk")});
        font.setPointSize(14);
        purpose->setFont(font);
        expression = new QLineEdit(Prompt);
        expression->setObjectName("expression");
        expression->setGeometry(QRect(32, 60, 451, 26));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Source Code Pro")});
        font1.setPointSize(12);
        font1.setItalic(true);
        expression->setFont(font1);

        retranslateUi(Prompt);
        QObject::connect(action, &QDialogButtonBox::accepted, Prompt, qOverload<>(&QDialog::accept));
        QObject::connect(action, &QDialogButtonBox::rejected, Prompt, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(Prompt);
    } // setupUi

    void retranslateUi(QDialog *Prompt)
    {
        Prompt->setWindowTitle(QCoreApplication::translate("Prompt", "Dialog", nullptr));
        purpose->setText(QCoreApplication::translate("Prompt", "Please enter raw expression", nullptr));
        expression->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Prompt: public Ui_Prompt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROMPT_H
