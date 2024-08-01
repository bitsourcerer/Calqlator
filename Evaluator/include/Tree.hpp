#pragma once

#include <queue>
#include "Expression.hpp"
#include "Parser.hpp"

namespace evaluator
{

namespace except {
struct evaluate_error : public evaluator_exception
{
    evaluate_error(const std::string &message = "Unspecified") : evaluator_exception("Evaluate Error | " + message) {}
};

struct missing_operand : public evaluate_error
{
    enum Type { FUNCTION, UNARY, BINARY };
    missing_operand(Type type)
        : evaluate_error("Missing Operand(s) to " + stringify(type))
    {
    }

    static std::string stringify(Type type)
    {
        std::string suffix;
        if(type == Type::BINARY) suffix = "Binary";
        else if(type == Type::UNARY) suffix = "Unary";
        else if(type == Type::FUNCTION) suffix = "Function";
        else suffix = "???";

        return std::string(suffix + (type == Type::FUNCTION ? "!" : " operation!"));
    }
};
}

	class EVALUATOR_API SyntaxTree
	{
        friend class Evaluator;
		using NodePtr = std::unique_ptr<Expression>;
        using ExprStack = Parser::VecStack<NodePtr>;
        using exception_t = except::evaluate_error;
	public:
		SyntaxTree();
        // SyntaxTree(const Parser::TokenQueue&);
        SyntaxTree(Parser::TokenQueue&&);

        SyntaxTree& build(Parser::TokenQueue &&tokens);
        EVALUATOR_UNUSED void set(Parser::TokenQueue &&tokens);

        EVALUATOR_UNUSED SyntaxTree& synthesize() {
            return build(std::move(tokens));
        }

        EVALUATOR_DEPRECATED Expression* getTree() const;
        Result evaluate() const;

	private:
		NodePtr root;
        EVALUATOR_UNUSED Parser::TokenQueue tokens; // not yet activated

        void clear() {
            root.reset(nullptr);
        }

        void validate_operands(unsigned short s, except::missing_operand::Type t) {
            unsigned short n = t == except::missing_operand::Type::FUNCTION ? 1 : static_cast<int>(t);
            // check if amount of operands in expression tree matches the given
            if(s < n) throw except::missing_operand(t);
        }
	};
}
