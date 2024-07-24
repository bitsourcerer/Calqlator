#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QPushButton>
#include "prompt.hpp"
#include "output.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void evaluate_expression(); // main function evaluates built expression
    void handle_digits(QAbstractButton*); // for all digits and dot
    void handle_commands(QAbstractButton*); // for commands like clear whole display, reset or backspace
    void handle_operations(QAbstractButton*); // for operations like add, subtract, multiply and divide
    void handle_functions(QAbstractButton*); // for functions like sin, cos, tan, log and natural logs
    void handle_parentheses(); // for parenthesis exclusively
    void generate_random(); // get random number [0, 1) when rand is clicked
    void devel_prompt(bool);
    // void output_pane(bool);

private:
    Ui::MainWindow *ui;
    Prompt *prompt;
    Output *out;

    void backspace() const;
    void reset() const;
    void clear() const;

    static void replace_subexpr(QString&);

    friend void debug(); // for debug purposes
};

enum OperationType { OPERAND, OPERATION, FUNCTION, PARENTHESES };

#endif // MAINWINDOW_HPP
