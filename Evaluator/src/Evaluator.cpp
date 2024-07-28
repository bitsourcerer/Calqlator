#include <stdexcept>
#include "Evaluator.hpp"

using namespace evaluator;

Evaluator::Evaluator(const std::string &infix) : input(infix), fed(true), parser(infix), tree(parser.parse()), lexer(infix)
{
}

Operand Evaluator::evaluate()
{
    auto root = tree.getTree();
    if (!fed || !root) throw except::evaluate_error("Tree Empty, Nothing to Evaluate!");
    return output = tree.evaluate();
}

Evaluator& Evaluator::feed(const std::string &str)
{
	input = str;
    // input = parser.feed(input).parse();
    // auto &&t = parser.feed(str).parse();
    // tree.build(std::move(t));
    lexer.set(input);

    try {
    auto &tokens = lexer.tokenize();
    auto &&parsed = parser.parse(tokens);
    tree.build(std::move(parsed));
    } catch(const std::exception&) {
        throw; // rethrow to be handled by top level eval function
    }

    // tree.build(parser.feed(str).parse());

	fed = true;
	return *this;
}
