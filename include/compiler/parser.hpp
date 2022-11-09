#include <iostream>

#include "lexer.hpp"

enum class StmtType {
	Variable,
	Expression,
	If,
	While,
	Print
};

enum class ExprType {
	Identifier,
	Value,
	Unary,
	Binary,
	Group,
	Call
};

class Expr;

class Stmt {
	public:

	StmtType Type;

	Token Subject = Token(0);

	Expr* Condition;

	Expr* Expression;

	std::vector<Stmt*> Block;

	Stmt(StmtType type) {
		Type = type;
	}
};

class Expr {
	public:

	ExprType Type;

	Expr* Left;
	Token Op;
	Expr* Right;

	Token Value;

	Expr(ExprType type) : Op(0), Value(0) {
		Type = type;
	}
};

class Parser {
	public:

	Lexer Lex;

	Stmt* Statement() {
		if (Lex.PeekToken().Convert<string>() == "let") {
			Lex.GetToken();

			Stmt* result = new Stmt(StmtType::Variable);
			
			result->Subject = Lex.GetToken();

			Lex.GetToken();

			result->Expression = Compare();

			if (Lex.PeekToken().Type == "Semicolon")
			Lex.GetToken();

			return result;
		}

		if (Lex.PeekToken().Convert<string>() == "print") {
			Lex.GetToken();

			Stmt* result = new Stmt(StmtType::Print);

			result->Expression = Compare();

			if (Lex.PeekToken().Type == "Semicolon")
			Lex.GetToken();

			return result;
		}

		if (Lex.PeekToken().Convert<string>() == "if") {
			Lex.GetToken();

			Stmt* result = new Stmt(StmtType::If);

			if (Lex.GetToken().Type != "LParen") {
				std::cout << "Expected (\n";
				
				throw new std::exception();
			}

			result->Condition = Compare();

			if (Lex.GetToken().Type != "RParen") {
				std::cout << "Expected )\n";
				
				throw new std::exception();
			}

			if (Lex.GetToken().Type != "LCurly") {
				std::cout << "Expected {\n";
				
				throw new std::exception();
			}

			std::vector<Stmt*> block = std::vector<Stmt*>();

			while (Lex.PeekToken().Type != "RCurly") {
				block.push_back(Statement());

				if (Lex.PeekToken().Type == "EOF") {
					std::cout << "Expected }\n";
				
					throw new std::exception();
				}
			}

			Lex.GetToken();

			result->Block = block;

			if (Lex.PeekToken().Type == "Semicolon")
			Lex.GetToken();

			return result;
		}

		if (Lex.PeekToken().Convert<string>() == "while") {
			Lex.GetToken();

			Stmt* result = new Stmt(StmtType::While);

			if (Lex.GetToken().Type != "LParen") {
				std::cout << "Expected (\n";
				
				throw new std::exception();
			}

			result->Condition = Compare();

			if (Lex.GetToken().Type != "RParen") {
				std::cout << "Expected )\n";
				
				throw new std::exception();
			}

			if (Lex.GetToken().Type != "LCurly") {
				std::cout << "Expected {\n";
				
				throw new std::exception();
			}

			std::vector<Stmt*> block = std::vector<Stmt*>();

			while (Lex.PeekToken().Type != "RCurly") {
				block.push_back(Statement());

				if (Lex.PeekToken().Type == "EOF") {
					std::cout << "Expected }\n";
				
					throw new std::exception();
				}
			}

			Lex.GetToken();

			result->Block = block;

			if (Lex.PeekToken().Type == "Semicolon")
			Lex.GetToken();

			return result;
		}
		
		Stmt* result = new Stmt(StmtType::Expression);

		result->Expression = Assign();

		if (Lex.PeekToken().Type == "Semicolon")
			Lex.GetToken();

		return result;
	}

	Expr* Assign() {
		if (Lex.PeekToken(2).Compare<string>("Op", "=")) {
			Token target = Lex.GetToken();

			Token op = Lex.GetToken();

			Expr* value = Compare();

			Expr* result = new Expr(ExprType::Binary);

			result->Value = target;

			result->Op = op;

			result->Right = value;

			return result;
		}

		return Compare();
	}

	Expr* Compare() {
		Expr* left = Add();

		if (Lex.PeekToken().Compare<string>("Op", "==")) {
			Expr* result = new Expr(ExprType::Binary);

			result->Left = left;

			result->Op = Lex.GetToken();

			result->Right = Add();

			return result;
		}

		if (Lex.PeekToken().Compare<string>("Op", ">")) {
			Expr* result = new Expr(ExprType::Binary);

			result->Left = left;

			result->Op = Lex.GetToken();

			result->Right = Add();

			return result;
		}

		return left;
	}

	Expr* Add() {
		Expr* left = Sub();

		if (Lex.PeekToken().Compare<string>("Op", "+")) {
			Expr* result = new Expr(ExprType::Binary);

			result->Left = left;

			result->Op = Lex.GetToken();

			result->Right = Sub();

			while (Lex.PeekToken().Compare<string>("Op", "+")) {
				Expr* binary = new Expr(ExprType::Binary);

				binary->Left = result->Right;

				binary->Op = Lex.GetToken();

				binary->Right = Sub();

				result->Right = binary;
			}

			return result;
		}

		return left;
	}

	Expr* Sub() {
		Expr* left = Mul();

		if (Lex.PeekToken().Compare<string>("Op", "-")) {
			Expr* result = new Expr(ExprType::Binary);

			result->Left = left;

			result->Op = Lex.GetToken();

			result->Right = Sub();

			return result;
		}

		return left;
	}

	Expr* Mul() {
		Expr* left = Div();

		if (Lex.PeekToken().Compare<string>("Op", "*")) {
			Expr* result = new Expr(ExprType::Binary);

			result->Left = left;

			result->Op = Lex.GetToken();

			result->Right = Mul();

			return result;
		}

		return left;
	}

	// Fix associativity later
	Expr* Div() {
		Expr* left = Literal();

		if (Lex.PeekToken().Compare<string>("Op", "/")) {
			Expr* result = new Expr(ExprType::Binary);

			result->Left = left;

			result->Op = Lex.GetToken();

			result->Right = Div();

			return result;
		}

		return left;
	}

	Expr* Literal() {
		if (Lex.PeekToken().Type == "LParen") {
			Lex.GetToken();

			Expr* expr = Compare();

			if (Lex.GetToken().Type != "RParen") {
				std::cout << "Expected )\n";

				throw new std::exception();
			}

			return expr;
		}
		Expr* result = new Expr(ExprType::Value);

		result->Value = Lex.GetToken();

		return result;
	}

	Parser(string src) : Lex(src) {
		
	}
};