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
        template <typename T> using VecStack = std::stack<T, std::vector<T>>;

		Parser() = default;
		Parser(std::string_view);
		Parser& feed(std::string_view);
        // [[MAYBE_UNUSED]] std::string parse() const;
        TokenQueue&& parse();
        TokenQueue&& getTokens();

	private:
		std::string input;
        // mutable std::string output; // removed permanently
        mutable TokenQueue tokens;
        static TokenQueue&& ShuntingYard(Parser *const);
	};
}
