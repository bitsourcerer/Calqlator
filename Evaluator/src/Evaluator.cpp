#include "Evaluator.h"
using namespace evaluator;

Evaluator::Evaluator(const std::string &infix) : input(infix), fed(true), parser(infix), tree(parser.parse())
{
}

Operand Evaluator::evaluate()
{
	if (!fed) throw std::invalid_argument("Nothing to Evaluate!");
	output = tree.evaluate();
	return output;
}

Evaluator& Evaluator::feed(const std::string &str)
{
	// TODO: insert return statement here
	input = str;
	input = parser.feed(input).parse();
	tree.build(parser.getTokens());
	// tree.buildFromVTokens(parser.convertToVTokens()); // todo make main stream

	fed = true;
	return *this;
}
