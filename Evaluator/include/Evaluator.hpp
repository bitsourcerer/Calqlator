#pragma once

#include "common.h"
#include "Lexer.hpp"
#include "Parser.hpp"
#include "Tree.hpp"

#include "Diagnostics.hpp"

namespace evaluator
{
	class EVALUATOR_API Evaluator
	{
	public:
        using TokenQueue = std::queue<UnifiedToken>;
        Evaluator();
		Evaluator(const std::string&);
		Operand evaluate();
		Evaluator & feed(const std::string & str);

	private:
		bool fed;
		std::string input;
		Operand output;

        diag::DiagnosticsHolder diagnostics;

        Lexer lexer;
		Parser parser;
		SyntaxTree tree;

        void reportDiagnostics() const;
	};
}
