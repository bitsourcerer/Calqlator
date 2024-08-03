#include <cstdlib>
#include "Diagnostics.hpp"

using namespace evaluator::diag;

Diagnostic::Diagnostic(Origin o, Level l, std::string_view m)
    : level(l), source(o), msg(stringify(o) + " " + stringify(l) + static_cast<std::string>(m))
{
}

void Diagnostic::report() const
{
    {
        switch(level)
        {
        case Level::LEVEL_INFO: case Level::LEVEL_WARNING:
            std::cout << msg << std::endl;
            break;

        case Level::LEVEL_ERROR:
            std::cerr << msg << std::endl;
            break;

        default:
            std::clog << "Unknown Log Level!\n";
            break;
        }
    }
}


std::string Diagnostic::stringify(Origin o)
{
    std::string str;
    switch (o) {
    case Origin::LEXER:
        str = "LEXER";
        break;

    case Origin::PARSER:
        str = "PARSER";
        break;

    case Origin::SYNTREE:
        str = "ASTREE";
        break;

    case Origin::EVALUATOR:
        str = "GENERAL";
        break;

    default:
        str = "Unknown";
        break;
    }
    return str;
}

std::string Diagnostic::stringify(Level l)
{
    std::string str;
    switch (l) {
    case Level::LEVEL_INFO:
        str = "Info";
        break;

    case Level::LEVEL_WARNING:
        str = "Warning";
        break;

    case Level::LEVEL_ERROR:
        str = "Error";
        break;

    default:
        "Log";
        break;
    }

    // str.append(" :: ");
    return str;
}


/* Diagnostic Holder */
DiagnosticsHolder::DiagnosticsHolder(Origin o)
{
    // o is unused
}

void DiagnosticsHolder::add(const Diagnostic &diag)
{
    if(!erroneous && diag.getLevel() == Level::LEVEL_ERROR) erroneous = true;
    diagnostics.push_back(diag);
}

void DiagnosticsHolder::add(Diagnostic &&diag)
{
    diagnostics.push_back(std::move(diag));
}

void DiagnosticsHolder::push(const Diagnostic &diag)
{
    add(diag);
}

void DiagnosticsHolder::push(Diagnostic &&diag)
{
    add(diag);
}

template <typename...Args>
void DiagnosticsHolder::emplace(Args&&...args)
{
    diagnostics.emplace_back(std::forward<Args>(args)...);
}

bool DiagnosticsHolder::hasError() const
{
    return erroneous;
    // std::any_of(diagnostics.cbegin(), diagnostics.cend(), [](const Diagnostic &d){ return d.getLevel() == Level::ERROR });
}

void DiagnosticsHolder::report() const
{
    for(const auto &d : diagnostics) d.report();
}

void DiagnosticsHolder::clear()
{
    diagnostics.clear();
    erroneous = false;
}

std::vector<Diagnostic>& DiagnosticsHolder::getDiagnostics()
{
    return diagnostics;
}


/* Diagnostics Adapter */
Diagnostics::Diagnostics(DiagnosticsHolder &dh, Origin o) : holder(dh), origin(o)
{
}

void Diagnostics::emit(Level level, std::string_view message)
{
    holder.emplace(origin, level, message);
}

void Diagnostics::warn(std::string_view message)
{
    holder.emplace(origin, Level::LEVEL_WARNING, message);
}

void Diagnostics::error(std::string_view message)
{
    holder.emplace(origin, Level::LEVEL_ERROR, message);
}
