#pragma once

#include "common.h"
#include "Parser.hpp"
#include "SyntaxTree.hpp"

namespace evaluator
{
	class EVALUATOR_API Evaluator
	{
	public:
        using TokenQueue = std::queue<UnifiedToken>;
		Evaluator() = default;
		Evaluator(const std::string&);
		Operand evaluate();
		Evaluator & feed(const std::string & str);

	private:
		bool fed;
		std::string input;
		Operand output;

		Parser parser;
		SyntaxTree tree;
	};
}
