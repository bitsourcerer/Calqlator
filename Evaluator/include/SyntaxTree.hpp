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
		SyntaxTree(const std::queue<Token>&);

		SyntaxTree& build(std::string_view expression);
		SyntaxTree& build(const std::queue<Token> &tokens);

		Result evaluate() const;

	private:
		NodePtr root;
	};

}
