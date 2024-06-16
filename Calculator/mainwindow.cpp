#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "includes.h"

#include <QDebug>
#include <QStack>
#include <QElapsedTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(370, 410);
    connect(ui->digits, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(handle_digits(QAbstractButton*)));
    connect(ui->commands, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(handle_commands(QAbstractButton*)));
    connect(ui->operations, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(handle_operations(QAbstractButton*)));
    connect(ui->lparen, SIGNAL(clicked()), this, SLOT(handle_parentheses()));
    connect(ui->rparen, SIGNAL(clicked()), this, SLOT(handle_parentheses()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

namespace {
bool ready = false; // to mimic windows's calculator's semantics
bool period = false; // number has a period (dot)
bool paren = false; // parentheses just closed, can't allow numbers directly without an operator first

QStack<std::string::size_type> markers;
QStack<Operand> subresults;
}

eval::Evaluator evl;

void MainWindow::on_evaluation_clicked()
{
    // static QString last;
    static QElapsedTimer watch;
    bool flag = false; // if markers are present we turn off replace_subexpr so that it doesnt cause problems

    auto expr = ui->equation->text();
    if(!expr.endsWith(')') && !expr.isEmpty()) expr.append(' ' + ui->number->text());
    if(!ready) return;

    ui->equation->clear();

    while(!markers.empty()) { expr += " )"; markers.pop(); flag = true; }
    expr = expr.trimmed();
    if(!flag) replace_subexpr(expr);

    qDebug() << "Evaluate: " << expr << '\n';

    // Mimic WinCalc evaluation on no operation supplied
    /*
     * auto opn = expr.toStdString().find_last_of("+-*%^/");
     * if(opn != std::string::npos) last = expr.mid(opn);
     * qDebug() << "Last: " << last << '\n';
     * if(ui->equation->text().isEmpty()) expr.append(' ' + last);
     */

    watch.start();
    auto result = evl.feed(expr.toStdString()).evaluate();
    qDebug() << "Result: " << result << " | Took " << (watch.nsecsElapsed() / 1e6) << " milliseconds!\n";
    ui->number->setText(QString::number(result));

    ready = paren = period = false;
}

void MainWindow::handle_digits(QAbstractButton *button)
{
    if(paren) { qWarning("Only Operations Allowed!\n"); return; }
    if(!ready) clear(); ready = true;

    auto btn = qobject_cast<QPushButton*>(button);
    auto num = ui->number->text();

    if(btn->text() == ".")
    {
        if(period) return;
        period = true;
    }
    // else if(btn->objectName() == "D0" && num == btn->text()) return; // if already 0 { can be optimized out by simply removing the line }

    ui->number->setText(num + btn->text());

    if(!period && num.startsWith('0'))
        ui->number->setText(ui->number->text().mid(1));
    // num.remove(0, 1);
}

void MainWindow::handle_commands(QAbstractButton *button)
{
    auto command = button->objectName();
    if(command == "reset")
    {
        reset();
    }
    else if(command == "clear")
    {
        clear();
    }
    else if(command == "backspace")
    {
        backspace();
    }
    else;
}

void MainWindow::handle_operations(QAbstractButton *button)
{
    auto btn = qobject_cast<QPushButton*>(button);
    auto eqn = ui->equation->text();
    auto num = ui->number->text();

    /* if(paren) {
        ui->equation->setText(eqn + " " + btn->text());
        paren = false;
        return;
    } */

    if(eqn == "Expression") eqn.clear();

    if(!eqn.isEmpty() && !eqn.endsWith(' ')) eqn.append(' ');
    if(!paren) eqn.append(num + ' ');
    ui->equation->setText(eqn + btn->text());

    paren = false;
    ready = false;
    // ui->equation->setText(eqn + num + " " + btn->text());
}

void MainWindow::handle_parentheses()
{
    auto btn = qobject_cast<QPushButton*>(sender());
    auto eqn = ui->equation->text();
    auto num = ui->number->text();

    static QString subexpr;

    if(!eqn.endsWith(' ')) eqn += ' ';

    if(btn == ui->rparen) // btn->objectName() == "rparen"
    {
        if(markers.empty()) return; // extra Right Paren ignored!
        if(!eqn.endsWith(btn->text())) eqn.append(num + ' ');

        subexpr = eqn.mid(markers.pop()) + ')';
        auto result = evl.feed(subexpr.toStdString()).evaluate();
        subresults.push(result);
        ui->number->setText(QString::number(result));

        paren = true;
    }
    else
    {
        if(eqn.endsWith(ui->rparen->text())) return;
        markers.push(eqn.length()); // pushed the length of string {off the end element} which will be paren.
    }

    ui->equation->setText(eqn + btn->text());
}

void MainWindow::reset() const
{
    clear();
    ui->equation->clear();
}

void MainWindow::clear() const
{
    ui->number->setText("0");
    period = false;
}

void MainWindow::backspace() const
{
    if(!ready) return; // don't backspace if not ready (windows calculator's behaviour)

    auto text = ui->number->text();
    auto dotPos = period ? text.indexOf('.') : -1; // Index of point in number!

    if(text.length() <= 1) clear();
    else
    {
        // text.truncate(text.length() - 1); // OR text.pop_back()
        text.chop(1);
        ui->number->setText(text);
        // qDebug() << "Backspaced: " << text << '\n';
    }
    if(period && text.length() <= dotPos) period = false; // equivalent to {dotPos >= text.length()} or {!(dotPos > text.length())}
    // if dot is also truncated then make it available again {if index is equal to length then that index is invalid}
}

void MainWindow::replace_subexpr(QString &eqn)
{
    static QSet<Operand> processed;
    // auto eqn = ui->equation->text();

    int current;
    while(!subresults.empty() && (current = eqn.lastIndexOf('(')) != -1)
    {
        Operand result = subresults.pop();
        if(processed.find(result) != processed.end()) continue;
        processed.insert(result);
        // eqn.mid(current, eqn.indexOf(')', current) - current + 1);
        eqn = eqn.replace(current, eqn.indexOf(')', current) - current + 1, QString::number(result));
    }
    // ui->equation->setText(eqn);
    processed.clear();
}
