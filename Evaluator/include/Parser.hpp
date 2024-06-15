#pragma once

#include "pch.h"
#include <queue>
#include <any>
#include <variant>
#include <type_traits>

#include "common.h"
#include "Precedence.hpp"

namespace evaluator
{
	class EVALUATOR_API OldToken
	{
	public:
		enum class EVALUATOR_API TokenType : char
		{
			OPERAND,
			OPERATION,
			LPAREN,
			RPAREN,
			PARENTHESIS,
			UNKNOWN
		};

		using Type = TokenType;
		OldToken() = default;
		OldToken(Operand num) : type(TokenType::OPERAND), value(num) { }
		OldToken(operations::BinaryOPS unr) : value(operations::OldOperation{unr}), type(TokenType::OPERATION) { }
		OldToken(operations::UnaryOPS bin) : value(operations::OldOperation{bin}), type(TokenType::OPERATION) { }
		OldToken(operations::Functions func) : type(TokenType::OPERATION), value(operations::OldOperation{func}) { }
		OldToken(operations::OldOperation ops) {
			// using operations::OldOperation::Type;
			switch (ops.type)
			{
			case operations::OldOperation::Type::BINARY:
			case operations::OldOperation::Type::UNARY:
				type = TokenType::OPERATION;
				break;
			case operations::OldOperation::Type::FUNCTION:
				type = TokenType::OPERATION;
				break;
			default:
				type = TokenType::UNKNOWN;
				value.reset();
				break;
			}
			value = ops;
			/*switch (ops.type)
			{
			case Type::BINARY:
				value = ops.b;
				type = TokenType::OPERATOR;
				break;
			case Type::UNARY:
				value = ops.u;
				type = TokenType::OPERATOR;
				break;
			case Type::FUNCTION:
				type = TokenType::FUNCTION;
				value = std::make_any<Functions>(ops.f);
				break;
			default:
				type = TokenType::UNKNOWN;
				value.reset();
				break;
			}*/
		}
		// auto getValue() const noexcept { return value; }
		TokenType getType() const noexcept { return type; }
		const std::any& getValue() const noexcept { return value; }

	private:
		TokenType type = TokenType::UNKNOWN;
		std::any value;
	};

	// using VariantOperation = std::variant<std::monostate, operations::UnaryOPS, operations::BinaryOPS, operations::Functions>;
	// using Token = std::variant<Operand, operations::UnaryOPS, operations::BinaryOPS, operations::Functions>;
	// using Token = std::variant<Operand, VariantOperation>;

	class EVALUATOR_API Parser
	{
	public:
		Parser() = default;
		Parser(std::string_view);
		Parser& feed(std::string_view);
		std::string parse() const;

		const std::queue<Token>& getTokens() const;
		std::queue<OldToken> convertToOld() const;

	private:
		std::string input;
		mutable std::string output;
		mutable std::queue<Token> tokens;

		static std::pair<std::string, std::queue<Token>> ShuntingYard(const std::string&);
	};

	/*
	template <> struct OldToken<TokenType::OPERAND> : IToken {
			double value;
			OldToken(double num) : value(num) { }
		};

		template <> struct OldToken<TokenType::OPERATOR> : IToken {
			char value;
			OldToken(char ops) : value(ops) { }
			OldToken(OldOperation binop) : value(binop) { }
			operator OldOperation() const { return static_cast<OldOperation>(value); }
		};*/
}
