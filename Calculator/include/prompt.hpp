#ifndef PROMPT_H
#define PROMPT_H

#include <QDialog>

namespace Ui {
class Prompt;
}

class Prompt : public QDialog
{
    Q_OBJECT
public:
    explicit Prompt(QWidget *parent = nullptr);
    ~Prompt();

    QString getExpression();

signals:
    // void gotExpression(const QString&);

private:
    Ui::Prompt *ui;
};

#endif // PROMPT_H
