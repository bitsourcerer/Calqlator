#pragma once

#ifndef DIAGNOSTICS_HPP
#define DIAGNOSTICS_HPP

#ifdef ERROR //  Windows.h SH!T
#undef ERROR
#endif

#include "common.h"

namespace evaluator::diag {

enum class Origin
{
    EVALUATOR,
    LEXER,
    PARSER,
    SYNTREE
};

enum Level // Windows.h problems
{
    LEVEL_INFO,
    LEVEL_WARNING,
    LEVEL_ERROR
};

class Diagnostic
{
public:
    Diagnostic(Origin, Level, std::string_view message);
    Level getLevel() const { return level; }
    Origin getSource() const { return source; }

    void report() const;

private:
    std::string msg;
    Level level = Level::LEVEL_INFO;
    Origin source = Origin::EVALUATOR;

    static std::string stringify(Level l);
    static std::string stringify(Origin o);
};


class DiagnosticsHolder
{
    // template <Origin> friend class Diagnostics;
public:
    DiagnosticsHolder(Origin oigin = Origin::EVALUATOR);

    void add(const Diagnostic&);
    void add(Diagnostic&&);

    void push(const Diagnostic&);
    void push(Diagnostic&&);

    template <typename...Args>
    void emplace(Args&&...args);

    bool hasError() const; // has Error?
    void report() const;

    void clear();

private:
    std::vector<Diagnostic> diagnostics;
    bool erroneous; // indicate whether the diagnostics contain an error (useful for termination)
    std::vector<Diagnostic>& getDiagnostics();
};

// template <Origin O>
class Diagnostics // Adapter for diagnostics Holder that omits specifying origin on every push
{
public:
    Diagnostics(DiagnosticsHolder&, Origin);
    Diagnostics(const Diagnostics&) = delete;
    Diagnostics(Diagnostics&&) = delete;

    void emit(Level level, std::string_view message);
    void warn(std::string_view message);
    void error(std::string_view message);

private:
    DiagnosticsHolder &holder;
    Origin origin; // the owner of this Diagnostics Accumulator
};

}

#endif // DIAGNOSTICS_HPP
