/********************************************************************************
** Form generated from reading UI file 'prompt.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROMPT_H
#define UI_PROMPT_H

#include <QtCore/QVariant>
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
            Prompt->setObjectName(QString::fromUtf8("Prompt"));
        Prompt->resize(515, 170);
        action = new QDialogButtonBox(Prompt);
        action->setObjectName(QString::fromUtf8("action"));
        action->setGeometry(QRect(60, 120, 341, 32));
        action->setOrientation(Qt::Horizontal);
        action->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        purpose = new QLabel(Prompt);
        purpose->setObjectName(QString::fromUtf8("purpose"));
        purpose->setGeometry(QRect(30, 10, 451, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("Padauk"));
        font.setPointSize(14);
        purpose->setFont(font);
        expression = new QLineEdit(Prompt);
        expression->setObjectName(QString::fromUtf8("expression"));
        expression->setGeometry(QRect(32, 60, 451, 26));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Source Code Pro"));
        font1.setPointSize(12);
        font1.setItalic(true);
        expression->setFont(font1);

        retranslateUi(Prompt);
        QObject::connect(action, SIGNAL(accepted()), Prompt, SLOT(accept()));
        QObject::connect(action, SIGNAL(rejected()), Prompt, SLOT(reject()));

        QMetaObject::connectSlotsByName(Prompt);
    } // setupUi

    void retranslateUi(QDialog *Prompt)
    {
        Prompt->setWindowTitle(QApplication::translate("Prompt", "Dialog", nullptr));
        purpose->setText(QApplication::translate("Prompt", "Please enter raw expression", nullptr));
        expression->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Prompt: public Ui_Prompt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROMPT_H
