#include <sstream>
#include <stack>
#include <cctype>

#include "common.h"
#include "Parser.hpp"
#include "Stack.hpp"

using namespace evaluator;
using namespace evaluator::operations;

// TODO : create custom exceptions for modules, like parse_error for Parser
class parse_error : std::logic_error
{
public:
    parse_error(const std::string &message = "Unspecifed") : std::logic_error("Parse Error | " + message) {}
    /*
    const char* what() const noexcept override {
    }
private:
    std::string msg = "Parse Error | "; */
};

Parser::Parser(std::string_view exp) : input(exp)
{
}

Parser& Parser::feed(std::string_view exp)
{
	input = exp;
	return *this;
}

Parser::TokenQueue&& Parser::parse()
{
    return ShuntingYard(*this);
}

Parser::TokenQueue&& Parser::getTokens()
{
    return std::move(tokens);
}

Parser::TokenQueue&& evaluator::ShuntingYard(Parser &parser)
{
    // Finite State Machine : digits, symbols, letters, parenthesis
    auto &tokens = parser.tokens;
    const auto &expression = parser.input;
    Parser::VecStack<UnifiedToken> operations;

    for (std::string::size_type i = 0; i != expression.length(); ++i)
    {
        const std::string::value_type current = expression.at(i);
        if (std::isspace(current)) continue;
        else if (
            BinaryOPS operation = static_cast<BinaryOPS>(current);
            binops.find(operation) != binops.end()
        )
        {
            if (!operations.empty())
            {
                auto top = operations.top();
                while (!(std::holds_alternative<Symbols>(top) && std::get<Symbols>(top) == Symbols::LPAREN)
                       &&  Precedence::check(std::get<BinaryOPS>(std::get<Operation>(top)), operation)) {
                    tokens.push(std::get<Operation>(operations.top())); operations.pop();
                    if(!operations.empty()) top = std::get<Operation>(operations.top());
                    else break;
                }
            }
            operations.push(operation);
        }
        else if (std::isalpha(current))
        {
            // lets assume the first token after any alphabet is '(' sqrt(10.0678)
            auto ite = std::find(expression.cbegin() + i, expression.cend(), ')'); // closing of function
            std::string::size_type start = expression.find_first_of('(', i+2);
            auto fn = expression.substr(i, start - i);
            auto itb = expression.cbegin() + i;

            if (operations::funcids.find(fn) == funcids.end()) continue; // not a registered function (not found in registry map)

            operations.push(funcids.at(fn));
            {
                std::string whole(itb, ite); whole.push_back(')'); // for debugging purposes
                Operand value = std::stod(whole.substr(fn.length() + 1));;

                tokens.push(value);
                tokens.push(std::get<Operation>(operations.top())); operations.pop();

                i += whole.length() - 1;
            }
        }
        else if (current == '(') operations.push(Symbols::LPAREN);
        else if (current == ')') // asserting whether operator stack is empty can indicate paren mismatch
        {
            if (operations.empty()) continue;
            for(auto top = operations.top();
                 !(std::holds_alternative<Symbols>(top) && std::get<Symbols>(top) == Symbols::LPAREN);
                top = operations.top(), operations.pop())
            {
                operations.pop();
                if (operations.empty()) throw std::logic_error("Parentheses Mismatch");
                tokens.push(std::get<Operation>(top));
            }
        }
        else if (std::ispunct(current) && current == ','); // pop all operators from operator stack into queue (while its not left paren)
        else if (std::isdigit(current) || current == '.')
        {
            std::size_t idx = 0;
            Operand value = std::stod(expression.substr(i), &idx);
            tokens.push(value);

            i = i + idx - 1; //--i;
        }
    }

    while (!operations.empty())
    {
        tokens.push(std::get<Operation>(operations.top()));
        operations.pop();
    }

    return std::move(tokens);
}

Parser::TokenQueue&& Parser::parse(Lexer::TokenQueue &lexed)
{
    // Consult Shunting Yard Algorithm's Wiki!
    Parser::VecStack<UnifiedToken> operations;
    VariantConverter converter;
    auto &tokens = this->tokens;

    while(!lexed.empty())
    {
        auto &&current = std::move(lexed.front());
        std::visit([&](auto &&token){
            using T = std::decay_t<decltype(token)>;
            // static_assert(std::is_same_v<T, OperationEnumeratorUnderlyingType>, "for some reason T is being converted to underlying type!");
            if constexpr(std::is_same_v<std::decay_t<T>, Operand>)
            {
                tokens.push(token);
            }
            else if constexpr(std::is_same_v<std::decay_t<T>, Operation>) // Operation itself is a variant
            {
                if (std::holds_alternative<Functions>(token)) {
                    // operations.push(token);
                    lexed.pop();
                    if(lexed.empty() || !std::holds_alternative<Operand>(lexed.front())) {
                        std::string fname = "unknown";
                        for(const auto &[name, id] : operations::funcids) if(id == std::get<Functions>(token)) fname = name;
                        std::cerr << "Missing operand to the function : " << fname << '\n';
                        throw parse_error("Operand Missing");
                    }
                    tokens.emplace(std::move(std::get<Operand>(lexed.front())));
                    tokens.push(token);
                }
                else {
                    auto operation = converter(token);
                    if (!operations.empty())
                    {
                        auto top = std::move(operations.top());
                        while (!(std::holds_alternative<Symbols>(top) && std::get<Symbols>(top) == Symbols::LPAREN)
                               &&  Precedence::check(converter(std::get<Operation>(top)), operation))
                        {
                            tokens.push(std::move(std::get<Operation>(operations.top()))); operations.pop();
                            if(!operations.empty()) top = operations.top();
                            else { std::cerr << "LParen Expected '('"; break;}
                        }
                    }
                    operations.push(token);
                }
            }
            else if constexpr(std::is_same_v<std::decay_t<T>, Symbols>)
            {
                switch(auto symbol = token)
                {
                case Symbols::LPAREN:
                    operations.push(Symbols::LPAREN);
                    break;

                case Symbols::RPAREN:
                {
                    if (operations.empty()) { std::cerr << "Parentheses Mismatch : Extra closing parentheses encountered!\n"; break; }
                    for(auto top = operations.top();
                         !(std::holds_alternative<Symbols>(top) && std::get<Symbols>(top) == Symbols::LPAREN);
                         top = operations.top(), operations.pop())
                    {
                        operations.pop();
                        if (operations.empty()) {
                            std::cerr << "Parentheses Mismatch : Expected corresponding opening parentheses!\n";
                            throw parse_error("Parentheses Mismatch");
                        }
                        tokens.push(std::get<Operation>(top));
                    }
                } break;

                default:
                    std::cerr << "Unexpected Symbol : " << static_cast<char>(symbol) << std::endl;
                    break;
                }
            }
            else throw parse_error("Unknown Token encountered while parsing!");
        }, current);
        lexed.pop();
    }

    while (!operations.empty())
    {
        if(std::holds_alternative<Operation>(operations.top()))
            tokens.push(std::move(std::get<Operation>(operations.top())));
        operations.pop();
    }

    return std::move(tokens);
}
