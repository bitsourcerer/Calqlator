#pragma once

#include <queue>

#include "Expression.hpp"

#ifdef MULTITHREAD
#include "shared/ThreadSafeQueue.hpp"
#else
template <typename> class ThreadSafeQueue;
#endif // MULTITHREAD


//class EVALUATOR_API STNode // UNUSED
//{
//	friend class SyntaxTree;
//	static constexpr Result NullValue = std::numeric_limits<Result>::infinity();
//public:
//	STNode() = default;
//	STNode(std::unique_ptr<Expression> exptr) : expression(std::move(exptr)), next(nullptr) { }
//	Result evaluate() {
//		result = expression->evaluate();
//		return 0.0;
//	};
//
//	virtual void unused() const = ABSTRACT;
//private:
//	std::unique_ptr<Expression> expression;
//	Result result = NullValue; // could be std::optional<Result>
//	std::shared_ptr<STNode> next;
//};

namespace evaluator
{
	class OldToken;
	// typename VariantToken;

	class EVALUATOR_API SyntaxTree
	{
		/*
		enum Notation { INFIX, POSTFIX, PREFIX }; // build may take notation type // default is RPN (postfix)
		*/
		using NodePtr = std::unique_ptr<Expression>;
	public:
		SyntaxTree();
		SyntaxTree(std::string_view expression);
		SyntaxTree(const std::queue<Token>&);
		SyntaxTree& build(std::string_view expression);
		SyntaxTree& build(const std::queue<Token> &tokens);
		SyntaxTree& buildFromOldTokens(const std::queue<OldToken> &tokens);
		Result evaluate() const;
	private:
		NodePtr root;
		// void assign(NodePtr node);
		// void assign(std::unique_ptr<Expression> expression);
		// NodePtr insert(std::unique_ptr<Expression> expression);
	};

}
