#include "../../include/compiler/compiler.hpp"

int Compiler::Expression(Expr* expr, Branch* branch) {
	if (expr->Type == ExprType::Binary) {
		if (expr->Op.Compare<string>("Op", "+")) {
			int cells = Memory.Allocate(2);

			branch->Add(new Move(branch, cells, Expression(expr->Left, branch)));

			branch->Add(new Move(branch, cells + 1, Expression(expr->Right, branch)));

			branch->Add(new Add(branch, cells, cells + 1));

			return cells;
		}

		if (expr->Op.Compare<string>("Op", "-")) {
			int cells = Memory.Allocate(2);

			branch->Add(new Move(branch, cells, Expression(expr->Left, branch)));

			branch->Add(new Move(branch, cells + 1, Expression(expr->Right, branch)));

			branch->Add(new Sub(branch, cells, cells + 1));

			return cells;
		}

		if (expr->Op.Compare<string>("Op", "*")) {
			int cells = Memory.Allocate(3);

			branch->Add(new Move(branch, cells + 1, Expression(expr->Left, branch)));

			branch->Add(new Move(branch, cells + 2, Expression(expr->Right, branch)));

			branch->Add(new Mul(branch, cells + 1, cells + 2));

			return cells + 1;
		}

		if (expr->Op.Compare<string>("Op", "/")) {
			int cells = Memory.Allocate(8);

			branch->Add(new Move(branch, cells + 1, Expression(expr->Left, branch)));

			branch->Add(new Move(branch, cells + 2, Expression(expr->Right, branch)));

			branch->Add(new Div(branch, cells + 1, cells + 2, cells + 3));

			return cells + 3 + 5;
		}

		if (expr->Op.Compare<string>("Op", "=")) {
			branch->Add(new Move(branch, Variables[expr->Value.Convert<string>()], Expression(expr->Right, branch)));

			return Variables[expr->Value.Convert<string>()];
		}

		if (expr->Op.Compare<string>("Op", ">")) {
			int cells = Memory.Allocate(7); // only 5 needed
				
			int left = Expression(expr->Left, branch);

			int right = Expression(expr->Right, branch);

			branch->Add(new Distance(branch, left, right, cells));

			Memory.Free(cells, 2);

			Memory.Free(cells + 4, 3);
			
			return cells + 3;
		}
			

		if (expr->Op.Compare<string>("Op", "==")) {
			int cell = Memory.Allocate(2);

			branch->Add(new Move(branch, cell, Expression(expr->Right, branch)));

			branch->Add(new Compare(branch, Expression(expr->Left, branch), cell));
	
			branch->Add(new Negate(branch, cell));

			return cell;
		}
	}

	if (expr->Type == ExprType::Value) {
		int cell = Memory.Allocate();

		if (expr->Value.Type == "Ident") {
			int temp = Memory.Allocate();

			branch->Add(new Copy(branch, cell, temp, Variables[expr->Value.Convert<string>()]));

			// Free temp here

			Memory.Free(temp);

			return cell;
		}
		
		branch->Add(new Set(branch, cell, expr->Value.Convert<int>()));

		return cell;
	}

	std::cout << ((int) expr->Type) << "\n";

	return 0;
}

void Compiler::Statement(Stmt* stmt, Branch* branch) {
	if (stmt->Type == StmtType::Variable) {
		int cell = Memory.Allocate();

		// std::cout << "Variable " << stmt->Subject.Convert<string>() << " = Cell " << cell << "\n";
		
		Variables[stmt->Subject.Convert<string>()] = cell;

		branch->Add(new Move(branch, cell, Expression(stmt->Expression, branch)));
		
		return;
	}

	if (stmt->Type == StmtType::If) {
		Branch* block = new Branch();

		int cond = Expression(stmt->Condition, branch);

		for (Stmt* st : stmt->Block) {
			Statement(st, block);
		}

		branch->Add(new If(branch, cond , block));

		return;
	}

	if (stmt->Type == StmtType::While) {
		Branch* block = new Branch(); // block->Add

		int cond = Expression(stmt->Condition, branch);
		
		for (Stmt* st : stmt->Block) {
			Statement(st, block);
		}

		block->Add(new Move(block, cond, Expression(stmt->Condition, block)));

		branch->Add(new Loop(branch, cond, block));
		
		return;
	}

	if (stmt->Type == StmtType::Print) {
		branch->Add(new Output(branch,  Expression(stmt->Expression, branch)));

		return;
	}

	Expression(stmt->Expression, branch);
}

string Compiler::Compile() {
	while (Source.Lex.PeekToken().Type != "EOF") {
		Stmt* stmt = Source.Statement();

		Statement(stmt, Gen->Layout);
	}

	return Gen->Compile();
}