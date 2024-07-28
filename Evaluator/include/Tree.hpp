#pragma once

#include <queue>
#include "Expression.hpp"

namespace evaluator
{
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

private:
    std::string msg;
};

}

	class EVALUATOR_API SyntaxTree
	{
		using NodePtr = std::unique_ptr<Expression>;
	public:
		SyntaxTree();
		SyntaxTree(std::string_view expression);
        // SyntaxTree(const Parser::TokenQueue&);
        SyntaxTree(Parser::TokenQueue&&);

		SyntaxTree& build(std::string_view expression);

        // SyntaxTree& build(const Parser::TokenQueue &tokens);
        SyntaxTree& build(Parser::TokenQueue &&tokens);

        Expression* getTree() const;
        EVALUATOR_DEPRECATED Result evaluate() const;

	private:
		NodePtr root;
	};
}
