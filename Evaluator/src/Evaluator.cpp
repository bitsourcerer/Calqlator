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
	input = str;
    // input = parser.feed(input).parse();
    parser.feed(str);
    tree.build(parser.getTokensByMove());

	fed = true;
	return *this;
}
