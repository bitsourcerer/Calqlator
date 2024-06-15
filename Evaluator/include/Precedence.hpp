#pragma once
#include "common.h"
#include "pch.h"

namespace evaluator
{
	enum OperatorPrecedence : std::underlying_type_t<operations::BinaryOPS>
	{
		MIN = 0,
		SUB = 1,
		ADD = 1,
		MUL = 2,
		DIV = 2,
		EXP = 3,
		MOD = 4,
		UNK, // UNKNOWN
		MAX // Maximum (for parenthesized subexpressions)
	};

	struct EVALUATOR_API Precedence // For Priority Queue
	{
		static const std::map < operations::BinaryOPS, OperatorPrecedence > precedence;

		// Precedence(const decltype(precedence) &precMap) : precedence(precMap) { }
		static bool checkPrecedence(operations::BinaryOPS left, operations::BinaryOPS right)
			// check if left has greater or equal precedence to right
		{
			const auto& lop = precedence.find(left)->second;
			const auto& rop = precedence.find(right)->second;
			// return std::less<OperatorPrecedence>{}(lop, rop);
			return std::greater_equal<OperatorPrecedence>{}(lop, rop);

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
}