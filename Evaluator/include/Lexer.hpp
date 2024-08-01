#pragma once

#include <queue>
#include <list>

#include "common.h"

namespace evaluator
{
namespace except {
class lexer_error : public std::exception
{
public:
    lexer_error(const std::string &message = "Unspecified") : msg("Syntax Error | ")
    {
        msg.append(message);
        msg.push_back('\n');
    }

    const char* what() const noexcept override {
        // std::string message = std::string("Syntax Error | ") + msg;
        // msg.insert(0, "Syntax Error | ");
        return msg.c_str();
    }
private:
    std::string msg;
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
