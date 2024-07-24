#pragma once

#include <queue>
#include <list>

#include "common.h"

namespace evaluator
{

class EVALUATOR_API Lexer
{
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
};

}
