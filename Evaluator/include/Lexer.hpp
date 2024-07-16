#pragma once

#include <queue>

#include "common.h"

namespace evaluator
{

class Lexer
{
public:
    using TokenQueue = std::queue<UnifiedToken>;
    Lexer() = default;
    Lexer(std::string_view);
    void set(std::string_view expr);
    TokenQueue&& tokenize() const;
    TokenQueue&& getTokens() const;

private:
    bool filled = false;
    std::string expression;
    mutable TokenQueue tokens;
};

}
