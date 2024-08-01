#pragma once

#include <queue>
#include "Expression.hpp"
#include "Parser.hpp"

namespace evaluator
{
class SyntaxTree;
namespace except {

class evaluate_error : public std::exception
{
public:
    evaluate_error(const std::string &message = "Unspecified") : msg("Evaluate Error | ")
    {
        msg.append(message);
        msg.push_back('\n');
    }

    const char* what() const noexcept override {
        // msg.insert(0, "Evaluate Error | ");
        return msg.c_str();
    }

protected:
    std::string msg;
};

struct missing_operand : public evaluate_error
{
    enum Type { FUNCTION, UNARY, BINARY };
    missing_operand(Type type)
        : evaluate_error("Missing Operand(s) to ")
    {
        std::string suffix;
        if(type == Type::BINARY) suffix = "Binary";
        else if(type == Type::UNARY) suffix = "Unary";
        else if(type == Type::FUNCTION) suffix = "Function";
        else suffix = "???";
        if(std::isspace(msg.back())) msg.pop_back();

        msg.append(suffix + (type == Type::FUNCTION ? "!" : " operation!"));
        msg.push_back('\n');
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
		SyntaxTree(std::string_view expression);
        // SyntaxTree(const Parser::TokenQueue&);
        SyntaxTree(Parser::TokenQueue&&);

		SyntaxTree& build(std::string_view expression);

        // SyntaxTree& build(const Parser::TokenQueue &tokens);
        SyntaxTree& build(Parser::TokenQueue &&tokens);
        void set(Parser::TokenQueue &&tokens);
        SyntaxTree& synthesize() {
            return build(std::move(tokens));
        }

        EVALUATOR_DEPRECATED Expression* getTree() const;
        Result evaluate() const;

	private:
		NodePtr root;
        Parser::TokenQueue tokens;

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
