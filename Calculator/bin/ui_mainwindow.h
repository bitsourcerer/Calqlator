/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *DevPrompt;
    QWidget *centralwidget;
    QFrame *Display;
    QLabel *number;
    QLabel *equation;
    QPushButton *D7;
    QPushButton *D8;
    QPushButton *D9;
    QPushButton *D6;
    QPushButton *D5;
    QPushButton *D4;
    QPushButton *D1;
    QPushButton *D2;
    QPushButton *D3;
    QPushButton *period;
    QPushButton *D0;
    QPushButton *subtraction;
    QPushButton *exponent;
    QPushButton *backspace;
    QPushButton *lparen;
    QPushButton *rparen;
    QPushButton *addition;
    QPushButton *modulus;
    QPushButton *reset;
    QPushButton *evaluation;
    QPushButton *multiplication;
    QPushButton *division;
    QPushButton *clear;
    QPushButton *logten;
    QPushButton *sqrt;
    QPushButton *tan;
    QPushButton *logn;
    QPushButton *rand;
    QPushButton *sin;
    QPushButton *fact;
    QPushButton *cos;
    QPushButton *logtwo;
    QPushButton *sign;
    QPushButton *baseten;
    QPushButton *powtwo;
    QStatusBar *statusbar;
    QMenuBar *menuBar;
    QMenu *MainMenu;
    QButtonGroup *digits;
    QButtonGroup *operations;
    QButtonGroup *commands;
    QButtonGroup *functions;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(640, 430);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Calculator.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setToolButtonStyle(Qt::ToolButtonIconOnly);
        DevPrompt = new QAction(MainWindow);
        DevPrompt->setObjectName(QString::fromUtf8("DevPrompt"));
        DevPrompt->setMenuRole(QAction::ApplicationSpecificRole);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        Display = new QFrame(centralwidget);
        Display->setObjectName(QString::fromUtf8("Display"));
        Display->setGeometry(QRect(10, 10, 621, 71));
        Display->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0, 1);\n"
"color: white;\n"
"border-radius: 5px;"));
        Display->setFrameShape(QFrame::StyledPanel);
        Display->setFrameShadow(QFrame::Raised);
        number = new QLabel(Display);
        number->setObjectName(QString::fromUtf8("number"));
        number->setGeometry(QRect(0, 30, 621, 41));
        QFont font;
        font.setFamily(QString::fromUtf8("OCR A Extended"));
        font.setPointSize(22);
        font.setBold(false);
        number->setFont(font);
        number->setStyleSheet(QString::fromUtf8("border: none;\n"
"padding: 5px;\n"
"background-color: transparent;"));
        number->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        equation = new QLabel(Display);
        equation->setObjectName(QString::fromUtf8("equation"));
        equation->setGeometry(QRect(10, -1, 601, 31));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Courier"));
        font1.setPointSize(10);
        equation->setFont(font1);
        equation->setStyleSheet(QString::fromUtf8("border: none;\n"
"background-color: transparent;"));
        D7 = new QPushButton(centralwidget);
        digits = new QButtonGroup(MainWindow);
        digits->setObjectName(QString::fromUtf8("digits"));
        digits->setExclusive(false);
        digits->addButton(D7);
        D7->setObjectName(QString::fromUtf8("D7"));
        D7->setGeometry(QRect(270, 160, 50, 40));
        D7->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(255, 255, 255, 0.85);\n"
"border-radius: 5px;"));
        D8 = new QPushButton(centralwidget);
        digits->addButton(D8);
        D8->setObjectName(QString::fromUtf8("D8"));
        D8->setGeometry(QRect(340, 160, 50, 40));
        D8->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(255, 255, 255, 0.85);\n"
"border-radius: 5px;"));
        D9 = new QPushButton(centralwidget);
        digits->addButton(D9);
        D9->setObjectName(QString::fromUtf8("D9"));
        D9->setGeometry(QRect(410, 160, 50, 40));
        D9->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(255, 255, 255, 0.85);\n"
"border-radius: 5px;"));
        D6 = new QPushButton(centralwidget);
        digits->addButton(D6);
        D6->setObjectName(QString::fromUtf8("D6"));
        D6->setGeometry(QRect(410, 220, 50, 40));
        D6->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(255, 255, 255, 0.85);\n"
"border-radius: 5px;"));
        D5 = new QPushButton(centralwidget);
        digits->addButton(D5);
        D5->setObjectName(QString::fromUtf8("D5"));
        D5->setGeometry(QRect(340, 220, 50, 40));
        D5->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(255, 255, 255, 0.85);\n"
"border-radius: 5px;"));
        D4 = new QPushButton(centralwidget);
        digits->addButton(D4);
        D4->setObjectName(QString::fromUtf8("D4"));
        D4->setGeometry(QRect(270, 220, 50, 40));
        D4->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(255, 255, 255, 0.85);\n"
"border-radius: 5px;"));
        D1 = new QPushButton(centralwidget);
        digits->addButton(D1);
        D1->setObjectName(QString::fromUtf8("D1"));
        D1->setGeometry(QRect(270, 280, 50, 40));
        D1->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(255, 255, 255, 0.85);\n"
"border-radius: 5px;"));
        D2 = new QPushButton(centralwidget);
        digits->addButton(D2);
        D2->setObjectName(QString::fromUtf8("D2"));
        D2->setGeometry(QRect(340, 280, 50, 40));
        D2->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(255, 255, 255, 0.85);\n"
"border-radius: 5px;"));
        D3 = new QPushButton(centralwidget);
        digits->addButton(D3);
        D3->setObjectName(QString::fromUtf8("D3"));
        D3->setGeometry(QRect(410, 280, 50, 40));
        D3->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(255, 255, 255, 0.85);\n"
"border-radius: 5px;"));
        period = new QPushButton(centralwidget);
        digits->addButton(period);
        period->setObjectName(QString::fromUtf8("period"));
        period->setGeometry(QRect(410, 340, 50, 40));
        period->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(255, 255, 255, 0.85);\n"
"border-radius: 5px;"));
        D0 = new QPushButton(centralwidget);
        digits->addButton(D0);
        D0->setObjectName(QString::fromUtf8("D0"));
        D0->setGeometry(QRect(270, 340, 121, 41));
        D0->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(255, 255, 255, 0.85);\n"
"border-radius: 5px;"));
        subtraction = new QPushButton(centralwidget);
        operations = new QButtonGroup(MainWindow);
        operations->setObjectName(QString::fromUtf8("operations"));
        operations->addButton(subtraction);
        subtraction->setObjectName(QString::fromUtf8("subtraction"));
        subtraction->setGeometry(QRect(500, 340, 51, 41));
        subtraction->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(240, 20, 20, 0.5);\n"
"color: white;\n"
"border-radius: 5px;"));
        exponent = new QPushButton(centralwidget);
        operations->addButton(exponent);
        exponent->setObjectName(QString::fromUtf8("exponent"));
        exponent->setGeometry(QRect(570, 220, 51, 41));
        exponent->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(240, 20, 20, 0.5);\n"
"color: white;\n"
"border-radius: 5px;"));
        backspace = new QPushButton(centralwidget);
        commands = new QButtonGroup(MainWindow);
        commands->setObjectName(QString::fromUtf8("commands"));
        commands->addButton(backspace);
        backspace->setObjectName(QString::fromUtf8("backspace"));
        backspace->setGeometry(QRect(413, 102, 50, 40));
        backspace->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(128, 128, 20, 0.35);\n"
"border-radius: 5px;"));
        lparen = new QPushButton(centralwidget);
        lparen->setObjectName(QString::fromUtf8("lparen"));
        lparen->setGeometry(QRect(500, 100, 51, 41));
        lparen->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(240, 20, 20, 0.5);\n"
"color: white;\n"
"border-radius: 5px;"));
        rparen = new QPushButton(centralwidget);
        rparen->setObjectName(QString::fromUtf8("rparen"));
        rparen->setGeometry(QRect(570, 100, 51, 41));
        rparen->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(240, 20, 20, 0.5);\n"
"color: white;\n"
"border-radius: 5px;"));
        addition = new QPushButton(centralwidget);
        operations->addButton(addition);
        addition->setObjectName(QString::fromUtf8("addition"));
        addition->setGeometry(QRect(500, 280, 51, 41));
        addition->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(240, 20, 20, 0.5);\n"
"color: white;\n"
"border-radius: 5px;"));
        modulus = new QPushButton(centralwidget);
        operations->addButton(modulus);
        modulus->setObjectName(QString::fromUtf8("modulus"));
        modulus->setGeometry(QRect(570, 160, 51, 41));
        modulus->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(240, 20, 20, 0.5);\n"
"color: white;\n"
"border-radius: 5px;"));
        reset = new QPushButton(centralwidget);
        commands->addButton(reset);
        reset->setObjectName(QString::fromUtf8("reset"));
        reset->setGeometry(QRect(271, 102, 50, 40));
        reset->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(128, 128, 20, 0.35);\n"
"border-radius: 5px;"));
        evaluation = new QPushButton(centralwidget);
        evaluation->setObjectName(QString::fromUtf8("evaluation"));
        evaluation->setGeometry(QRect(570, 280, 51, 101));
        evaluation->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(20, 20, 240, 1);\n"
"color: white;\n"
"border-radius: 5px;"));
        multiplication = new QPushButton(centralwidget);
        operations->addButton(multiplication);
        multiplication->setObjectName(QString::fromUtf8("multiplication"));
        multiplication->setGeometry(QRect(500, 220, 51, 41));
        multiplication->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(240, 20, 20, 0.5);\n"
"color: white;\n"
"border-radius: 5px;"));
        division = new QPushButton(centralwidget);
        operations->addButton(division);
        division->setObjectName(QString::fromUtf8("division"));
        division->setGeometry(QRect(500, 160, 51, 41));
        division->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(240, 20, 20, 0.5);\n"
"color: white;\n"
"border-radius: 5px;"));
        clear = new QPushButton(centralwidget);
        commands->addButton(clear);
        clear->setObjectName(QString::fromUtf8("clear"));
        clear->setGeometry(QRect(340, 100, 50, 40));
        clear->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(128, 128, 20, 0.35);\n"
"border-radius: 5px;"));
        logten = new QPushButton(centralwidget);
        functions = new QButtonGroup(MainWindow);
        functions->setObjectName(QString::fromUtf8("functions"));
        functions->addButton(logten);
        logten->setObjectName(QString::fromUtf8("logten"));
        logten->setGeometry(QRect(50, 220, 50, 40));
        logten->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(255, 255, 255, 0.85);\n"
"border-radius: 5px;"));
        sqrt = new QPushButton(centralwidget);
        functions->addButton(sqrt);
        sqrt->setObjectName(QString::fromUtf8("sqrt"));
        sqrt->setGeometry(QRect(190, 280, 50, 40));
        sqrt->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(255, 255, 255, 0.85);\n"
"border-radius: 5px;"));
        tan = new QPushButton(centralwidget);
        functions->addButton(tan);
        tan->setObjectName(QString::fromUtf8("tan"));
        tan->setGeometry(QRect(190, 160, 50, 40));
        tan->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(255, 255, 255, 0.85);\n"
"border-radius: 5px;"));
        logn = new QPushButton(centralwidget);
        functions->addButton(logn);
        logn->setObjectName(QString::fromUtf8("logn"));
        logn->setGeometry(QRect(120, 220, 50, 40));
        logn->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(255, 255, 255, 0.85);\n"
"border-radius: 5px;"));
        rand = new QPushButton(centralwidget);
        rand->setObjectName(QString::fromUtf8("rand"));
        rand->setGeometry(QRect(120, 280, 50, 40));
        rand->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(255, 255, 255, 0.85);\n"
"border-radius: 5px;"));
        sin = new QPushButton(centralwidget);
        functions->addButton(sin);
        sin->setObjectName(QString::fromUtf8("sin"));
        sin->setGeometry(QRect(50, 160, 50, 40));
        sin->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(255, 255, 255, 0.85);\n"
"border-radius: 5px;"));
        fact = new QPushButton(centralwidget);
        functions->addButton(fact);
        fact->setObjectName(QString::fromUtf8("fact"));
        fact->setGeometry(QRect(50, 280, 50, 40));
        fact->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(255, 255, 255, 0.85);\n"
"border-radius: 5px;"));
        cos = new QPushButton(centralwidget);
        functions->addButton(cos);
        cos->setObjectName(QString::fromUtf8("cos"));
        cos->setGeometry(QRect(120, 160, 50, 40));
        cos->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(255, 255, 255, 0.85);\n"
"border-radius: 5px;"));
        logtwo = new QPushButton(centralwidget);
        functions->addButton(logtwo);
        logtwo->setObjectName(QString::fromUtf8("logtwo"));
        logtwo->setGeometry(QRect(190, 220, 50, 40));
        logtwo->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(255, 255, 255, 0.85);\n"
"border-radius: 5px;"));
        sign = new QPushButton(centralwidget);
        functions->addButton(sign);
        sign->setObjectName(QString::fromUtf8("sign"));
        sign->setGeometry(QRect(120, 340, 50, 40));
        sign->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(255, 255, 255, 0.85);\n"
"border-radius: 5px;"));
        baseten = new QPushButton(centralwidget);
        baseten->setObjectName(QString::fromUtf8("baseten"));
        baseten->setGeometry(QRect(190, 340, 50, 40));
        baseten->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(255, 255, 255, 0.85);\n"
"border-radius: 5px;"));
        powtwo = new QPushButton(centralwidget);
        functions->addButton(powtwo);
        powtwo->setObjectName(QString::fromUtf8("powtwo"));
        powtwo->setGeometry(QRect(50, 340, 50, 40));
        powtwo->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(255, 255, 255, 0.85);\n"
"border-radius: 5px;"));
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 640, 23));
        MainMenu = new QMenu(menuBar);
        MainMenu->setObjectName(QString::fromUtf8("MainMenu"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(MainMenu->menuAction());
        MainMenu->addAction(DevPrompt);

        retranslateUi(MainWindow);

        evaluation->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Calculator", nullptr));
        DevPrompt->setText(QApplication::translate("MainWindow", "Developer Input", nullptr));
#ifndef QT_NO_TOOLTIP
        DevPrompt->setToolTip(QApplication::translate("MainWindow", "Input Custom Expression", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        DevPrompt->setShortcut(QApplication::translate("MainWindow", "Ctrl+D", nullptr));
#endif // QT_NO_SHORTCUT
        number->setText(QApplication::translate("MainWindow", "Calculator", nullptr));
        equation->setText(QString());
        D7->setText(QApplication::translate("MainWindow", "7", nullptr));
        D8->setText(QApplication::translate("MainWindow", "8", nullptr));
        D9->setText(QApplication::translate("MainWindow", "9", nullptr));
        D6->setText(QApplication::translate("MainWindow", "6", nullptr));
        D5->setText(QApplication::translate("MainWindow", "5", nullptr));
        D4->setText(QApplication::translate("MainWindow", "4", nullptr));
        D1->setText(QApplication::translate("MainWindow", "1", nullptr));
        D2->setText(QApplication::translate("MainWindow", "2", nullptr));
        D3->setText(QApplication::translate("MainWindow", "3", nullptr));
        period->setText(QApplication::translate("MainWindow", ".", nullptr));
        D0->setText(QApplication::translate("MainWindow", "0", nullptr));
        subtraction->setText(QApplication::translate("MainWindow", "-", nullptr));
        exponent->setText(QApplication::translate("MainWindow", "^", nullptr));
        backspace->setText(QApplication::translate("MainWindow", "<-", nullptr));
        lparen->setText(QApplication::translate("MainWindow", "(", nullptr));
        rparen->setText(QApplication::translate("MainWindow", ")", nullptr));
        addition->setText(QApplication::translate("MainWindow", "+", nullptr));
        modulus->setText(QApplication::translate("MainWindow", "%", nullptr));
        reset->setText(QApplication::translate("MainWindow", "C", nullptr));
        evaluation->setText(QApplication::translate("MainWindow", "=", nullptr));
        multiplication->setText(QApplication::translate("MainWindow", "*", nullptr));
        division->setText(QApplication::translate("MainWindow", "/", nullptr));
        clear->setText(QApplication::translate("MainWindow", "AC", nullptr));
        logten->setText(QApplication::translate("MainWindow", "log", nullptr));
        sqrt->setText(QApplication::translate("MainWindow", "sqrt", nullptr));
        tan->setText(QApplication::translate("MainWindow", "tan", nullptr));
        logn->setText(QApplication::translate("MainWindow", "ln", nullptr));
        rand->setText(QApplication::translate("MainWindow", "rand", nullptr));
        sin->setText(QApplication::translate("MainWindow", "sin", nullptr));
        fact->setText(QApplication::translate("MainWindow", "n!", nullptr));
        cos->setText(QApplication::translate("MainWindow", "cos", nullptr));
        logtwo->setText(QApplication::translate("MainWindow", "log2", nullptr));
        sign->setText(QApplication::translate("MainWindow", "+/-", nullptr));
        baseten->setText(QApplication::translate("MainWindow", "EE", nullptr));
        powtwo->setText(QApplication::translate("MainWindow", "x^2", nullptr));
        MainMenu->setTitle(QApplication::translate("MainWindow", "Menu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
