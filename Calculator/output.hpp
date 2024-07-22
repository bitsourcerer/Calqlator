#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include <QWidget>
#include <QIODevice>
#include <QTextBrowser>

namespace Ui {
class Output;
}

class OutputRedirector;
class textbrowser_streambuf;

class Output : public QWidget
{
    Q_OBJECT
public:
    explicit Output(QWidget *parent = nullptr);
    ~Output();

private slots:
    void clear(); // clear text browser
    void appendText(const QString&);

private:
    Ui::Output *ui;
    textbrowser_streambuf *stdred;
    std::streambuf *coutBuf, *cerrBuf;
    // OutputRedirector *stdred;
};

class OutputRedirector : public QIODevice
{
    Q_OBJECT

public:
    explicit OutputRedirector(QTextBrowser *out, QObject *parent = nullptr);
    virtual ~OutputRedirector();

    bool open(OpenMode mode) override;
    void close() override;

protected:
    qint64 readData(char *data, qint64 maxSize) override;
    qint64 writeData(const char *data, qint64 maxSize) override;

private:
    QTextBrowser *browser;
};

class textbrowser_streambuf : public QObject, public std::streambuf
{
    Q_OBJECT

public:
    textbrowser_streambuf(QTextBrowser *browser);
    virtual ~textbrowser_streambuf();

protected:
    traits_type::int_type overflow(int_type c) override;
    std::streamsize xsputn(const char *s, std::streamsize n) override;

signals:
    void received(const QString&);

private:
    QTextBrowser *text;
    std::string buffer;
};

#endif // OUTPUT_HPP
