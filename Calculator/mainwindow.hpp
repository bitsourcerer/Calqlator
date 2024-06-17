#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QPushButton>

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
    void handle_parentheses(); // for parenthesis exclusively

private:
    Ui::MainWindow *ui;
    void backspace() const;
    void reset() const;
    void clear() const;

    static void replace_subexpr(QString&);
};
#endif // MAINWINDOW_HPP
