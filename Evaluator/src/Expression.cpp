#include <stdexcept>
#include "Expression.hpp"

using namespace evaluator;
using namespace evaluator::operations;

Number::Number(double _value) : value(_value)
{
}

Result Number::evaluate() const noexcept
{
	return value;
}

Unary::Unary(std::unique_ptr<Expression> _value, char _operator) : value(std::move(_value)), operation(static_cast<operations::UnaryOPS>(_operator))
{
}

evaluator::Unary::Unary(std::unique_ptr<Expression> val, UnaryOPS op) : value(std::move(val)), operation(op)
{
}

Result Unary::evaluate() const noexcept
{
    return operation == UnaryOPS::NEGATION ? -value->evaluate() : value->evaluate();
}

Binary::Binary(VExpression lhs, VExpression rhs, BinaryOPS oper) : left(std::move(lhs)), right(std::move(rhs))
,operation(oper)
{
}

Result Binary::evaluate() const
{
	Operand l = left->evaluate(), r = right->evaluate();
	Result ret = 0.0;
	if (binops.find(operation) != binops.end())
	{
        ret = binops[operation](l, r);
	}
	else throw std::domain_error("Unlisted Operation Used!");
	return ret;
};

Function::Function(std::unique_ptr<Expression> val, operations::Functions func) : value(std::move(val)), function(func)
{
}

Result Function::evaluate() const
{
	return operations::funcs.at(function)(value->evaluate());
}
