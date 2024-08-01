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

enum class StreamType { STD_OUT, STD_ERR };

class Output : public QWidget
{
    Q_OBJECT
public:
    explicit Output(QWidget *parent = nullptr);
    ~Output();

signals:
    void logEmitted(bool); // to signal to other widgets that the log is received (the param tells if its an error or not)
    void expressionEntered(QString);

private slots:
    void clear(); // clear text browser
    void appendText(const QString&, StreamType type);
    void evaluateExpr();

private:
    Ui::Output *ui;
    textbrowser_streambuf *redcerr, *redcout;
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
    textbrowser_streambuf(QTextBrowser *browser, StreamType type = StreamType::STD_OUT);
    // virtual ~textbrowser_streambuf();

protected:
    traits_type::int_type overflow(int_type c) override;
    std::streamsize xsputn(const char_type *s, std::streamsize n) override;

signals:
    void received(const QString&, StreamType);

private:
    QTextBrowser *text;
    std::string buffer;
    StreamType type;
};

#endif // OUTPUT_HPP
