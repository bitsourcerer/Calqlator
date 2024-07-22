#include "output.hpp"
#include "ui_output.h"

#include <iostream>

Output::Output(QWidget *parent)
    : QWidget{parent}, ui(new Ui::Output), stdred(new textbrowser_streambuf{ui->text})
{
    ui->setupUi(this);

    connect(ui->clear, SIGNAL(clicked()), this, SLOT(clear()));
    connect(stdred, SIGNAL(received(QString)), this, SLOT(appendText(QString)));

    // stdred->open(QIODevice::WriteOnly);
    coutBuf = std::cout.rdbuf(stdred);
    cerrBuf = std::cerr.rdbuf(stdred);

    ui->text->append("<----------|| Beginning of the Output ||---------->");
}

Output::~Output()
{
    delete ui;
}

void Output::clear()
{
    ui->text->clear();
}

void Output::appendText(const QString &text)
{
    ui->text->append(text);
}

OutputRedirector::OutputRedirector(QTextBrowser *out, QObject *parent)
    : QIODevice(parent), browser(out)
{
}

OutputRedirector::~OutputRedirector()
{
    close();
}

bool OutputRedirector::open(OpenMode mode)
{
    setOpenMode(mode);
    return true;
}

void OutputRedirector::close()
{
    setOpenMode(NotOpen);
}

qint64 OutputRedirector::readData(char *data, qint64 maxSize)
{
    Q_UNUSED(data);
    Q_UNUSED(maxSize);
    return -1;
}

qint64 OutputRedirector::writeData(const char *data, qint64 maxSize)
{
    if(!browser) return -1;
    browser->moveCursor(QTextCursor::End);
    browser->insertPlainText(QString::fromLocal8Bit(data, maxSize));
    browser->moveCursor(QTextCursor::End);

    return maxSize;
}

textbrowser_streambuf::textbrowser_streambuf(QTextBrowser *browser)
    : text(browser)
{
}

textbrowser_streambuf::~textbrowser_streambuf()
{
    overflow('\n');
}

textbrowser_streambuf::int_type textbrowser_streambuf::overflow(int_type c)
{
    if(c != traits_type::eof())
    {
        buffer += static_cast<char>(c);
        if(c == '\n')
        {
            // text->append(QString::fromStdString(buffer));
            emit received(QString::fromStdString(buffer));
            buffer.clear();
        }
    }
    return c;
}

std::streamsize textbrowser_streambuf::xsputn(const char *s, std::streamsize n)
{
    buffer.append(s, n);
    std::size_t pos = 0;
    while((pos = buffer.find('\n')) != std::string::npos)
    {
        // text->append(QString::fromStdString(buffer.substr(0, pos)));
        emit received(QString::fromStdString(buffer.substr(0, pos)));
        buffer.erase(0, pos + 1);
    }
    return n;
}
