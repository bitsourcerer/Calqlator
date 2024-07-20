#include <stdexcept>
#include "Evaluator.hpp"

using namespace evaluator;

Evaluator::Evaluator(const std::string &infix) : input(infix), fed(true), parser(infix), tree(parser.parse()), lexer(infix)
{
}

Operand Evaluator::evaluate()
{
    if (!fed) throw std::invalid_argument("Nothing to Evaluate!");
    return output = tree.evaluate();
}

Evaluator& Evaluator::feed(const std::string &str)
{
	input = str;
    // input = parser.feed(input).parse();
    // auto &&t = parser.feed(str).parse();
    // tree.build(std::move(t));
    lexer.set(input);

    auto &tokens = lexer.tokenize();
    auto &&parsed = parser.parse(tokens);
    tree.build(std::move(parsed));
    // tree.build(parser.feed(str).parse());

	fed = true;
	return *this;
}
