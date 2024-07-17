#include "prompt.hpp"
#include "ui_prompt.h"

Prompt::Prompt(QWidget *parent) : QDialog(parent), ui(new Ui::Prompt)
{
    ui->setupUi(this);
}

Prompt::~Prompt()
{
    delete ui;
}

QString Prompt::getExpression()
{
    return ui->expression->text();
    ui->expression->clear();
}
