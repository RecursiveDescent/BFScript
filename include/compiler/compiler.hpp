#include <map>
#include <algorithm>

#include "../framework.hpp"

#include "parser.hpp"

class CellManager {
	public:

	int Start = 0;

	int Size = 0;

	std::vector<int> Used = std::vector<int>();

	std::vector<int> Freed = std::vector<int>();

	int Position;

	void Free(int cell, int size = 1) {
		for (int i = cell; i < cell + size; i++) {
			std::remove(Used.begin(), Used.end(), i);
		}
	}

	// TODO more complex allocator
	int Allocate(int size = 1) {
		int start = Position;
		
		for (int i = 0; i < size; i++) {
			Used.push_back(Start + Position++);
		}

		Size += size;

		return start;
	}
};

class Compiler {
	public:

	Parser Source;

	Generator* Gen;

	std::map<string, int> Variables = std::map<string, int>();

	CellManager Memory = CellManager();

	int Expression(Expr* expr, Branch* branch);

	void Statement(Stmt* stmt, Branch* branch);

	string Compile();

	Compiler(string src) : Source(src) {
		Gen = new Generator();
	}
};