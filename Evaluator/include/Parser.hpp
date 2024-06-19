#pragma once

#include <queue>
#include <type_traits>
#include <list>
#include <utility>

#include "common.h"
#include "Precedence.hpp"

namespace evaluator
{
	class EVALUATOR_API Parser
    {
	public:
        using TokenQueue = std::queue<Token>; // using std::list as backend increases time of the first evaluation and doesnt yield much

		Parser() = default;
		Parser(std::string_view);
		Parser& feed(std::string_view);
        // [[MAYBE_UNUSED]] std::string parse() const;
        TokenQueue&& parse();
        const std::string& parseStr() const;

        // const std::queue<Token>& getTokens() const;
        TokenQueue&& getTokensByMove();

	private:
		std::string input;
		mutable std::string output;
        mutable TokenQueue tokens;

        static std::pair<std::string, TokenQueue> ShuntingYard(const std::string&);
        static TokenQueue&& ShuntingYard(Parser *const);
	};
}
