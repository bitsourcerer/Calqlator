#pragma once

#include <queue>
// #include <type_traits>
// #include <list>
#include <utility>

#include "common.h"
#include "Lexer.hpp"
#include "Precedence.hpp"

namespace evaluator
{
namespace except {
// TODO : create custom exceptions for modules, like parse_error for Parser
struct parse_error : public evaluator_exception
{
    parse_error(const std::string &message = "Unspecifed") : evaluator_exception("Parse Error | " + message) {}
};

struct parentheses_mismatch : public parse_error
{
    parentheses_mismatch(const std::string &message = "unspecified") : parse_error("Parentheses Mismatch : " + message) {}
};

}

class EVALUATOR_API Parser
{
    friend class Evaluator;
    using exception_t = except::parse_error;
public:
    using TokenQueue = std::queue<Token>; // using std::list as backend increases time of the first evaluation and doesnt yield much
    template <typename T> using VecStack = std::stack<T, std::vector<T>>;
    friend TokenQueue&& ShuntingYard(Parser&);

    Parser() = default;
    Parser(Lexer::TokenQueue&);
    // Parser& feed(Lexer::TokenQueue&);
    // [[MAYBE_UNUSED]] std::string parse() const;
    TokenQueue&& parse();
    Parser::TokenQueue&& parse(Lexer::TokenQueue&);
    TokenQueue&& getTokens();

private:
    mutable TokenQueue tokens;

    void clear() const {
        while(!tokens.empty()) tokens.pop();
    }
    // static TokenQueue&& ShuntingYard(Parser *const);
};

Parser::TokenQueue&& ShuntingYard(Parser&);
}
