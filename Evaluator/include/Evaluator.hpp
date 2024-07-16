#pragma once

#include "common.h"
#include "Lexer.hpp"
#include "Parser.hpp"
#include "Tree.hpp"

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

        Lexer lexer;
		Parser parser;
		SyntaxTree tree;
	};
}
