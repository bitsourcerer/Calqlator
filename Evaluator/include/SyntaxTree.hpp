#pragma once

#include <queue>
#include "Expression.hpp"

namespace evaluator
{
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

		Result evaluate() const;

	private:
		NodePtr root;
	};
}
