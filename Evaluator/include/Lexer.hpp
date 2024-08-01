#pragma once

#include <queue>
#include <list>

#include "common.h"

namespace evaluator
{
namespace except {
struct lexer_error : public evaluator_exception
{
    lexer_error(const std::string &message = "Unspecified") : evaluator_exception("Lexer Error | " + message) {}
};

}

class EVALUATOR_API Lexer
{
    friend class Evaluator;
    using exception_t = except::lexer_error;
public:
    // using TokenQueue = std::queue<UnifiedToken, std::list<UnifiedToken>>;
    using TokenQueue = std::queue<UnifiedToken>;
    Lexer() = default;
    Lexer(std::string_view);
    void set(std::string_view expr);
    TokenQueue& tokenize() const;
    TokenQueue& getTokens() const;

private:
    std::string expression;
    bool filled = false;
    mutable TokenQueue tokens;

    void clear() const {
        if(!tokens.empty()) tokens = TokenQueue();
    }
};

}

/*
class lexer_error : public std::exception
{
public:
    lexer_error(const std::string &message = "Unspecified") : msg("Syntax Error | ")
    {
        if(msg.find('\n', msg.length() / 2) != std::string::npos) nl = true;
        msg.append(message);
    }

    const char* what() const noexcept override {
        if(!nl) msg.push_back('\n');
        // std::string message = std::string("Syntax Error | ") + msg;
        // msg.insert(0, "Syntax Error | ");
        return msg.c_str();
    }

private:
    std::string msg;
    bool nl = false;
};
*/
