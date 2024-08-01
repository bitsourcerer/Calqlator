#include <stdexcept>
#include "Evaluator.hpp"

using namespace evaluator;

Evaluator::Evaluator(const std::string &infix) : fed(true), input(infix)
    , lexer(infix), parser(lexer.tokenize()), tree(parser.parse())
{
}

Operand Evaluator::evaluate()
{
    /*auto root = tree.getTree();
    if (!fed || !root) throw except::evaluate_error("Tree Empty, Nothing to Evaluate!");
    return output = root->evaluate();*/
    return output = tree.evaluate();
}

Evaluator& Evaluator::feed(const std::string &str)
{
	input = str;

    lexer.set(input);

    try {
    auto &tokens = lexer.tokenize();
    auto &&parsed = parser.parse(tokens);
    tree.build(std::move(parsed));
    } catch(const except::lexer_error&) {
        lexer.clear();
        throw;
    } catch(const except::parse_error&) {
        lexer.clear();
        parser.clear();
        throw;
    } catch(const except::evaluate_error&) {
        tree.clear();
        parser.clear();
        throw;
    } catch(const std::exception&) {
        /*
        lexer.clear();
        parser.clear();
        tree.clear();
        */

        fed = false;
        throw; // rethrow to be handled by top level eval function
    }

	fed = true;
	return *this;
}
