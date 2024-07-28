#include "output.hpp"
#include "ui_output.h"

#include <iostream>

Output::Output(QWidget *parent)
    : QWidget{parent, Qt::Window}, ui(new Ui::Output)
    , redcerr(new textbrowser_streambuf{ui->text, StreamType::STD_ERR})
    , redcout(new textbrowser_streambuf{ui->text, StreamType::STD_OUT})
{
    ui->setupUi(this);

    connect(ui->clear, SIGNAL(clicked()), this, SLOT(clear()));
    connect(redcerr, SIGNAL(received(QString, StreamType)), this, SLOT(appendText(QString, StreamType)));
    connect(redcout, SIGNAL(received(QString, StreamType)), this, SLOT(appendText(QString, StreamType)));

    // stdred->open(QIODevice::WriteOnly);
    coutBuf = std::cout.rdbuf(redcout);
    cerrBuf = std::cerr.rdbuf(redcerr);

    ui->text->setTextColor(Qt::darkGreen);
    ui->text->append(QString("<----------|| Beginning of the Output ||---------->") + '\n');
    ui->text->moveCursor(QTextCursor::End);
}

Output::~Output()
{
    delete ui;
    std::cout.rdbuf(coutBuf);
    std::cerr.rdbuf(cerrBuf);
    // close();
}

void Output::clear()
{
    ui->text->clear();
}

void Output::appendText(const QString &text, StreamType type)
{
    if(type == StreamType::STD_ERR) {
        ui->text->setTextColor(Qt::red);
        ui->text->insertPlainText("ERROR :: ");
        this->show(); // if error is logged open the output pane
    } else {
        ui->text->setTextColor(Qt::black);
        ui->text->insertPlainText("LOG :: ");
    }
    ui->text->insertPlainText(text);
    emit logEmitted(type == StreamType::STD_ERR); // emit and tell if error is received
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

textbrowser_streambuf::textbrowser_streambuf(QTextBrowser *browser, StreamType type)
    : text(browser), type(type)
{
}

/*
textbrowser_streambuf::~textbrowser_streambuf()
{
    // sync();
} */

textbrowser_streambuf::int_type textbrowser_streambuf::overflow(int_type c)
{
    if(c != traits_type::eof())
    {
        /*
        char buf[2] = { static_cast<char>(c), '\0' };
        emit received(QString::fromLatin1(buf), type);
        return c;
        */

        // below flushes on newline
        buffer += static_cast<char>(c);
        if(c == '\n')
        {
            // text->append(QString::fromStdString(buffer));
            emit received(QString::fromStdString(buffer), type);
            buffer.clear();
        }
    }
    return c;
}

std::streamsize textbrowser_streambuf::xsputn(const char_type *s, std::streamsize n)
{
    /*
    emit received(QString::fromLatin1(s, static_cast<int>(n)), type);
    return n;
    */

    buffer.append(s, n);

    std::size_t pos = 0;
    while((pos = buffer.find('\n')) != std::string::npos)
    {
        // text->append(QString::fromStdString(buffer.substr(0, pos)));
        // emit received(QString::fromStdString(buffer.substr(0, pos)), type); // excludes the newline
        emit received(QString::fromStdString(buffer.substr(0, pos + 1)), type); // includes the newline
        buffer.erase(0, pos + 1);
    }
    return n;
}
