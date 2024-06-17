#pragma once

#include <queue>
#include <any>
#include <variant>
#include <type_traits>

#include "common.h"
#include "Precedence.hpp"

namespace evaluator
{
	class EVALUATOR_API Parser
	{
	public:
		Parser() = default;
		Parser(std::string_view);
		Parser& feed(std::string_view);
		std::string parse() const;

        // const std::queue<Token>& getTokens() const;
        std::queue<Token>&& getTokensByMove();

	private:
		std::string input;
		mutable std::string output;
		mutable std::queue<Token> tokens;

		static std::pair<std::string, std::queue<Token>> ShuntingYard(const std::string&);
	};
}
