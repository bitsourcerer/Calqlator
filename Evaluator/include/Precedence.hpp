#pragma once
#include "common.h"

namespace evaluator
{
enum OperatorPrecedence : operations::OperationEnumeratorUnderlyingType //std::underlying_type_t<operations::BinaryOPS>
	{
		MIN = 0,
		SUB = 1,
		ADD = 1,
		MUL = 2,
		DIV = 2,
		EXP = 3,
		MOD = 4,
        UNR = 5, // for Unary Operations
		UNK, // UNKNOWN
        MAX, // Maximum (for parenthesized subexpressions and functions)
        FUN = MAX
	};

	struct EVALUATOR_API Precedence // For Priority Queue
	{
        // using Operator = std::variant<std::monostate, operations::BinaryOPS, operations::UnaryOPS, operations::Functions>;
        using Operator = Operation;
        static const std::map < Operator, OperatorPrecedence > precedenceTable;
        static std::greater_equal<OperatorPrecedence> comparator;

		// Precedence(const decltype(precedence) &precMap) : precedence(precMap) { }
        static bool check(Operator left, Operator right)
			// check if left has greater or equal precedence to right
		{
            // monostate generally represents functions but we can do better by adding Functions in Operator Variant
            // if(std::holds_alternative<std::monostate>(left) || std::holds_alternative<std::monostate>(right)) return false;
            const auto& lop = precedenceTable.find(left)->second;
            const auto& rop = precedenceTable.find(right)->second;
			// return std::less<OperatorPrecedence>{}(lop, rop);
            return comparator(lop, rop);

			/*int precedence = 0;
			for (const auto& [k, v] : prec)
			{
				if (false);
				precedence = static_cast<int>(std::max(left, right));
			}*/
		}
		auto operator()(operations::BinaryOPS op) {
			return static_cast<int>(op);
		}
	};

    struct VariantConverter
    {
        Precedence::Operator operator()(operations::BinaryOPS op) const { return op; }
        Precedence::Operator operator()(operations::UnaryOPS op) const { return op; }
        Precedence::Operator operator()(operations::Functions op) const { return op; }
        Precedence::Operator operator()(...) const { return Precedence::Operator{}; }

        Precedence::Operator operator()(Operation op) const {
            return std::visit([this](const auto &o) {
                return (*this) (o);
            }, op);
        }
    };
}
