/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
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
    QPushButton *exponentiation;
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
    QPushButton *log10;
    QPushButton *sqrt;
    QPushButton *tan;
    QPushButton *loge;
    QPushButton *RANDOM;
    QPushButton *sin;
    QPushButton *FACTORIAL;
    QPushButton *cos;
    QPushButton *log2;
    QPushButton *POW;
    QPushButton *BASE10;
    QPushButton *POW2;
    QStatusBar *statusbar;
    QMenuBar *menuBar;
    QButtonGroup *commands;
    QButtonGroup *operations;
    QButtonGroup *functions;
    QButtonGroup *digits;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(663, 420);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Calculator.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setToolButtonStyle(Qt::ToolButtonIconOnly);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        Display = new QFrame(centralwidget);
        Display->setObjectName("Display");
        Display->setGeometry(QRect(10, 10, 641, 71));
        Display->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0, 1);\n"
"color: white;\n"
"border-radius: 5px;"));
        Display->setFrameShape(QFrame::StyledPanel);
        Display->setFrameShadow(QFrame::Raised);
        number = new QLabel(Display);
        number->setObjectName("number");
        number->setGeometry(QRect(0, 30, 631, 41));
        QFont font;
        font.setFamilies({QString::fromUtf8("OCR A Extended")});
        font.setPointSize(22);
        font.setBold(false);
        number->setFont(font);
        number->setStyleSheet(QString::fromUtf8("border: none;\n"
"padding: 5px;\n"
"background-color: transparent;"));
        number->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        equation = new QLabel(Display);
        equation->setObjectName("equation");
        equation->setGeometry(QRect(10, -1, 621, 31));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Courier")});
        font1.setPointSize(10);
        equation->setFont(font1);
        equation->setStyleSheet(QString::fromUtf8("border: none;\n"
"background-color: transparent;"));
        D7 = new QPushButton(centralwidget);
        digits = new QButtonGroup(MainWindow);
        digits->setObjectName("digits");
        digits->setExclusive(false);
        digits->addButton(D7);
        D7->setObjectName("D7");
        D7->setGeometry(QRect(290, 160, 50, 40));
        D7->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(255, 255, 255, 0.85);\n"
"border-radius: 5px;"));
        D8 = new QPushButton(centralwidget);
        digits->addButton(D8);
        D8->setObjectName("D8");
        D8->setGeometry(QRect(360, 160, 50, 40));
        D8->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(255, 255, 255, 0.85);\n"
"border-radius: 5px;"));
        D9 = new QPushButton(centralwidget);
        digits->addButton(D9);
        D9->setObjectName("D9");
        D9->setGeometry(QRect(430, 160, 50, 40));
        D9->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(255, 255, 255, 0.85);\n"
"border-radius: 5px;"));
        D6 = new QPushButton(centralwidget);
        digits->addButton(D6);
        D6->setObjectName("D6");
        D6->setGeometry(QRect(430, 220, 50, 40));
        D6->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(255, 255, 255, 0.85);\n"
"border-radius: 5px;"));
        D5 = new QPushButton(centralwidget);
        digits->addButton(D5);
        D5->setObjectName("D5");
        D5->setGeometry(QRect(360, 220, 50, 40));
        D5->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(255, 255, 255, 0.85);\n"
"border-radius: 5px;"));
        D4 = new QPushButton(centralwidget);
        digits->addButton(D4);
        D4->setObjectName("D4");
        D4->setGeometry(QRect(290, 220, 50, 40));
        D4->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(255, 255, 255, 0.85);\n"
"border-radius: 5px;"));
        D1 = new QPushButton(centralwidget);
        digits->addButton(D1);
        D1->setObjectName("D1");
        D1->setGeometry(QRect(290, 280, 50, 40));
        D1->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(255, 255, 255, 0.85);\n"
"border-radius: 5px;"));
        D2 = new QPushButton(centralwidget);
        digits->addButton(D2);
        D2->setObjectName("D2");
        D2->setGeometry(QRect(360, 280, 50, 40));
        D2->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(255, 255, 255, 0.85);\n"
"border-radius: 5px;"));
        D3 = new QPushButton(centralwidget);
        digits->addButton(D3);
        D3->setObjectName("D3");
        D3->setGeometry(QRect(430, 280, 50, 40));
        D3->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(255, 255, 255, 0.85);\n"
"border-radius: 5px;"));
        period = new QPushButton(centralwidget);
        digits->addButton(period);
        period->setObjectName("period");
        period->setGeometry(QRect(430, 340, 50, 40));
        period->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(255, 255, 255, 0.85);\n"
"border-radius: 5px;"));
        D0 = new QPushButton(centralwidget);
        digits->addButton(D0);
        D0->setObjectName("D0");
        D0->setGeometry(QRect(290, 340, 121, 41));
        D0->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(255, 255, 255, 0.85);\n"
"border-radius: 5px;"));
        subtraction = new QPushButton(centralwidget);
        operations = new QButtonGroup(MainWindow);
        operations->setObjectName("operations");
        operations->addButton(subtraction);
        subtraction->setObjectName("subtraction");
        subtraction->setGeometry(QRect(520, 340, 51, 41));
        subtraction->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(240, 20, 20, 0.5);\n"
"color: white;\n"
"border-radius: 5px;"));
        exponentiation = new QPushButton(centralwidget);
        operations->addButton(exponentiation);
        exponentiation->setObjectName("exponentiation");
        exponentiation->setGeometry(QRect(590, 220, 51, 41));
        exponentiation->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(240, 20, 20, 0.5);\n"
"color: white;\n"
"border-radius: 5px;"));
        backspace = new QPushButton(centralwidget);
        commands = new QButtonGroup(MainWindow);
        commands->setObjectName("commands");
        commands->addButton(backspace);
        backspace->setObjectName("backspace");
        backspace->setGeometry(QRect(433, 102, 50, 40));
        backspace->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(128, 128, 20, 0.35);\n"
"border-radius: 5px;"));
        lparen = new QPushButton(centralwidget);
        lparen->setObjectName("lparen");
        lparen->setGeometry(QRect(520, 100, 51, 41));
        lparen->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(240, 20, 20, 0.5);\n"
"color: white;\n"
"border-radius: 5px;"));
        rparen = new QPushButton(centralwidget);
        rparen->setObjectName("rparen");
        rparen->setGeometry(QRect(590, 100, 51, 41));
        rparen->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(240, 20, 20, 0.5);\n"
"color: white;\n"
"border-radius: 5px;"));
        addition = new QPushButton(centralwidget);
        operations->addButton(addition);
        addition->setObjectName("addition");
        addition->setGeometry(QRect(520, 280, 51, 41));
        addition->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(240, 20, 20, 0.5);\n"
"color: white;\n"
"border-radius: 5px;"));
        modulus = new QPushButton(centralwidget);
        operations->addButton(modulus);
        modulus->setObjectName("modulus");
        modulus->setGeometry(QRect(590, 160, 51, 41));
        modulus->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(240, 20, 20, 0.5);\n"
"color: white;\n"
"border-radius: 5px;"));
        reset = new QPushButton(centralwidget);
        commands->addButton(reset);
        reset->setObjectName("reset");
        reset->setGeometry(QRect(291, 102, 50, 40));
        reset->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(128, 128, 20, 0.35);\n"
"border-radius: 5px;"));
        evaluation = new QPushButton(centralwidget);
        evaluation->setObjectName("evaluation");
        evaluation->setGeometry(QRect(590, 280, 51, 101));
        evaluation->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(20, 20, 240, 1);\n"
"color: white;\n"
"border-radius: 5px;"));
        multiplication = new QPushButton(centralwidget);
        operations->addButton(multiplication);
        multiplication->setObjectName("multiplication");
        multiplication->setGeometry(QRect(520, 220, 51, 41));
        multiplication->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(240, 20, 20, 0.5);\n"
"color: white;\n"
"border-radius: 5px;"));
        division = new QPushButton(centralwidget);
        operations->addButton(division);
        division->setObjectName("division");
        division->setGeometry(QRect(520, 160, 51, 41));
        division->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(240, 20, 20, 0.5);\n"
"color: white;\n"
"border-radius: 5px;"));
        clear = new QPushButton(centralwidget);
        commands->addButton(clear);
        clear->setObjectName("clear");
        clear->setGeometry(QRect(360, 100, 50, 40));
        clear->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(128, 128, 20, 0.35);\n"
"border-radius: 5px;"));
        log10 = new QPushButton(centralwidget);
        functions = new QButtonGroup(MainWindow);
        functions->setObjectName("functions");
        functions->addButton(log10);
        log10->setObjectName("log10");
        log10->setGeometry(QRect(70, 220, 50, 40));
        log10->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(255, 255, 255, 0.85);\n"
"border-radius: 5px;"));
        sqrt = new QPushButton(centralwidget);
        functions->addButton(sqrt);
        sqrt->setObjectName("sqrt");
        sqrt->setGeometry(QRect(210, 280, 50, 40));
        sqrt->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(255, 255, 255, 0.85);\n"
"border-radius: 5px;"));
        tan = new QPushButton(centralwidget);
        functions->addButton(tan);
        tan->setObjectName("tan");
        tan->setGeometry(QRect(210, 160, 50, 40));
        tan->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(255, 255, 255, 0.85);\n"
"border-radius: 5px;"));
        loge = new QPushButton(centralwidget);
        functions->addButton(loge);
        loge->setObjectName("loge");
        loge->setGeometry(QRect(140, 220, 50, 40));
        loge->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(255, 255, 255, 0.85);\n"
"border-radius: 5px;"));
        RANDOM = new QPushButton(centralwidget);
        RANDOM->setObjectName("RANDOM");
        RANDOM->setGeometry(QRect(140, 280, 50, 40));
        RANDOM->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(255, 255, 255, 0.85);\n"
"border-radius: 5px;"));
        sin = new QPushButton(centralwidget);
        functions->addButton(sin);
        sin->setObjectName("sin");
        sin->setGeometry(QRect(70, 160, 50, 40));
        sin->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(255, 255, 255, 0.85);\n"
"border-radius: 5px;"));
        FACTORIAL = new QPushButton(centralwidget);
        FACTORIAL->setObjectName("FACTORIAL");
        FACTORIAL->setGeometry(QRect(70, 280, 50, 40));
        FACTORIAL->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(255, 255, 255, 0.85);\n"
"border-radius: 5px;"));
        cos = new QPushButton(centralwidget);
        functions->addButton(cos);
        cos->setObjectName("cos");
        cos->setGeometry(QRect(140, 160, 50, 40));
        cos->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(255, 255, 255, 0.85);\n"
"border-radius: 5px;"));
        log2 = new QPushButton(centralwidget);
        functions->addButton(log2);
        log2->setObjectName("log2");
        log2->setGeometry(QRect(210, 220, 50, 40));
        log2->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(255, 255, 255, 0.85);\n"
"border-radius: 5px;"));
        POW = new QPushButton(centralwidget);
        POW->setObjectName("POW");
        POW->setGeometry(QRect(140, 340, 50, 40));
        POW->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(255, 255, 255, 0.85);\n"
"border-radius: 5px;"));
        BASE10 = new QPushButton(centralwidget);
        BASE10->setObjectName("BASE10");
        BASE10->setGeometry(QRect(210, 340, 50, 40));
        BASE10->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(255, 255, 255, 0.85);\n"
"border-radius: 5px;"));
        POW2 = new QPushButton(centralwidget);
        POW2->setObjectName("POW2");
        POW2->setGeometry(QRect(70, 340, 50, 40));
        POW2->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color: rgba(255, 255, 255, 0.85);\n"
"border-radius: 5px;"));
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 663, 23));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        evaluation->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Calculator", nullptr));
        number->setText(QCoreApplication::translate("MainWindow", "Calculator", nullptr));
        equation->setText(QString());
        D7->setText(QCoreApplication::translate("MainWindow", "7", nullptr));
        D8->setText(QCoreApplication::translate("MainWindow", "8", nullptr));
        D9->setText(QCoreApplication::translate("MainWindow", "9", nullptr));
        D6->setText(QCoreApplication::translate("MainWindow", "6", nullptr));
        D5->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        D4->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        D1->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        D2->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        D3->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        period->setText(QCoreApplication::translate("MainWindow", ".", nullptr));
        D0->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        subtraction->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        exponentiation->setText(QCoreApplication::translate("MainWindow", "^", nullptr));
        backspace->setText(QCoreApplication::translate("MainWindow", "<-", nullptr));
        lparen->setText(QCoreApplication::translate("MainWindow", "(", nullptr));
        rparen->setText(QCoreApplication::translate("MainWindow", ")", nullptr));
        addition->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        modulus->setText(QCoreApplication::translate("MainWindow", "%", nullptr));
        reset->setText(QCoreApplication::translate("MainWindow", "C", nullptr));
        evaluation->setText(QCoreApplication::translate("MainWindow", "=", nullptr));
        multiplication->setText(QCoreApplication::translate("MainWindow", "*", nullptr));
        division->setText(QCoreApplication::translate("MainWindow", "/", nullptr));
        clear->setText(QCoreApplication::translate("MainWindow", "AC", nullptr));
        log10->setText(QCoreApplication::translate("MainWindow", "log", nullptr));
        sqrt->setText(QCoreApplication::translate("MainWindow", "sqrt", nullptr));
        tan->setText(QCoreApplication::translate("MainWindow", "tan", nullptr));
        loge->setText(QCoreApplication::translate("MainWindow", "ln", nullptr));
        RANDOM->setText(QCoreApplication::translate("MainWindow", "rand", nullptr));
        sin->setText(QCoreApplication::translate("MainWindow", "sin", nullptr));
        FACTORIAL->setText(QCoreApplication::translate("MainWindow", "n!", nullptr));
        cos->setText(QCoreApplication::translate("MainWindow", "cos", nullptr));
        log2->setText(QCoreApplication::translate("MainWindow", "log2", nullptr));
        POW->setText(QCoreApplication::translate("MainWindow", "x^y", nullptr));
        BASE10->setText(QCoreApplication::translate("MainWindow", "EE", nullptr));
        POW2->setText(QCoreApplication::translate("MainWindow", "x^2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
