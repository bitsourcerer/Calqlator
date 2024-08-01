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
class parse_error : public std::logic_error
{
public:
    parse_error(const std::string &message = "Unspecifed") : std::logic_error("Parse Error | " + message + "\n") {}
    /*
    const char* what() const noexcept override {
    }
private:
    std::string msg = "Parse Error | "; */
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

    /*
    namespace test
    {

    struct BinaryOperation {
        operations::BinaryOPS type = operations::BinaryOPS::UNSPECIFIED;
        OperatorPrecedence precdence = OperatorPrecedence::MIN;
    };

    struct UnaryOperation {
        operations::UnaryOPS type = operations::UnaryOPS::UNSPECIFIED;
        OperatorPrecedence precedence = OperatorPrecedence::MIN;
    };

    struct FunctionOperation {
        operations::Functions type = operations::Functions::UNSPECIFIED;
        unsigned arg_count = 0;
    };

    }*/
}
