#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "interpreter.hpp"

extern bool Comment;

#define COMMENT(text) (Comment ? text : "")

class Branch;

class Generator;

class MemoryBlock {
	public:

	Generator* Branch; // Which branch to access and write from

	int Position;

	int Size;

	void Write(int offset, int value);

	MemoryBlock(Generator* gen, int pos, int size);
};

class MemoryStack: public MemoryBlock {
	public:

	int StackSize = 0;

	void Push(int value);

	void Pop(int cell);

	MemoryStack(Generator* gen, int pos, int size) : MemoryBlock(gen, pos, size) {};
};

class Instruction {
	public:

	Branch* Owner;

	Branch* Br = nullptr;

	virtual void Simulate(Generator* gen, int* cptr, bool memory = false) {};

	virtual Instruction* Compile(Generator* gen, int* cptr, std::string& output) {};
};

class Goto : public Instruction {
	public:

	int Target;

	void Simulate(Generator* gen, int* cptr, bool memory = false) override {
		*cptr = Target;
	}

	Instruction* Compile(Generator* gen, int* cptr, std::string& output) override;

	Goto(Branch* owner, int target);
};

class Set : public Instruction {
	public:

	int Target;

	int Value;

	void Simulate(Generator* gen, int* cptr, bool memory = false) override;

	Instruction* Compile(Generator* gen, int* cptr, std::string& output) override;

	Set(Branch* owner, int target, int value) {
		Owner = owner;

		Target = target;

		Value = value;
	}
};

class Copy : public Instruction {
	public:

	int Target;

	int Temp;

	int Source;

	void Simulate(Generator* gen, int* cptr, bool memory = false) override;

	Instruction* Compile(Generator* gen, int* cptr, std::string& output) override;

	Copy(Branch* owner, int target, int temp, int source) {
		Owner = owner;

		Target = target;

		Temp = temp;

		Source = source;
	}
};

class Move : public Instruction {
	public:

	int Target;

	int Source;

	void Simulate(Generator* gen, int* cptr, bool memory = false) override;

	Instruction* Compile(Generator* gen, int* cptr, std::string& output) override;

	Move(Branch* owner, int target, int source) {
		Owner = owner;

		Target = target;

		Source = source;
	}
};

class Add : public Instruction {
	public:

	int A;

	int B;

	void Simulate(Generator* gen, int* cptr, bool memory = false) override;

	Instruction* Compile(Generator* gen, int* cptr, std::string& output) override;

	Add(Branch* owner, int a, int b) {
		Owner = owner;

		A = a;

		B = b;
	}
};

class Sub : public Instruction {
	public:

	int A;

	int B;

	void Simulate(Generator* gen, int* cptr, bool memory = false) override;

	Instruction* Compile(Generator* gen, int* cptr, std::string& output) override;

	Sub(Branch* owner, int a, int b) {
		Owner = owner;

		A = a;

		B = b;
	}
};

class Mul : public Instruction {
	public:

	int A;

	int B;

	void Simulate(Generator* gen, int* cptr, bool memory = false) override;

	Instruction* Compile(Generator* gen, int* cptr, std::string& output) override;

	Mul(Branch* owner, int a, int b) {
		Owner = owner;

		A = a;

		B = b;
	}
};

class Div : public Instruction {
	public:

	int A;

	int B;

	int Location; // + 1 = remainder, + 5 = quotient

	void Simulate(Generator* gen, int* cptr, bool memory = false) override;

	Instruction* Compile(Generator* gen, int* cptr, std::string& output) override;

	Div(Branch* owner, int a, int b, int location) {
		Owner = owner;

		A = a;

		B = b;

		Location = location;
	}
};

class If : public Instruction {
	public:

	int Condition;

	void Simulate(Generator* gen, int* cptr, bool memory = false) override;

	Instruction* Compile(Generator* gen, int* cptr, std::string& output) override;

	If(Branch* owner, int condition, Branch* br) {
		Owner = owner;

		Condition = condition;

		Br = br;
	}
};

class Loop : public Instruction {
	public:

	int Condition;

	void Simulate(Generator* gen, int* cptr, bool memory = false) override;

	Instruction* Compile(Generator* gen, int* cptr, std::string& output) override;

	Loop(Branch* owner, int condition, Branch* br) {
		Owner = owner;

		Condition = condition;

		Br = br;
	}
};

class Compare : public Instruction {
	public:

	int A;

	int B;

	void Simulate(Generator* gen, int* cptr, bool memory = false) override;

	Instruction* Compile(Generator* gen, int* cptr, std::string& output) override;

	Compare(Branch* owner, int a, int b) {
		Owner = owner;

		A = a;

		B = b;
	}
};

class Negate : public Instruction {
	public:

	int A;

	void Simulate(Generator* gen, int* cptr, bool memory = false) override;

	Instruction* Compile(Generator* gen, int* cptr, std::string& output) override;

	Negate(Branch* owner, int a) {
		Owner = owner;

		A = a;
	}
};


class Output : public Instruction {
	public:

	int A;

	void Simulate(Generator* gen, int* cptr, bool memory = false) override {
		
	};

	Instruction* Compile(Generator* gen, int* cptr, std::string& output) override;

	Output(Branch* owner, int a) {
		Owner = owner;

		A = a;
	}
};

class Distance : public Instruction {
	public:

	int A;

	int B;

	int Location; // + 3 = A, + 5 = B

	void Simulate(Generator* gen, int* cptr, bool memory = false) override;

	Instruction* Compile(Generator* gen, int* cptr, std::string& output) override;

	Distance(Branch* owner, int a, int b, int location) {
		Owner = owner;

		A = a;

		B = b;

		Location = location;
	}
};

class Generator {

	public:

	Branch* Layout;

	Interpreter Analyzer = Interpreter();

	std::string Output = "";

	std::vector<int> Cells = std::vector<int>();

	int Cell = 0;

	int IndentLevel = 0;

	std::string Indent();

	void Set(int cell, int value);

	MemoryBlock AcquireBlock(int pos, int size);

	std::string Compile();

	Generator();
};

class Branch {
	public:

	Branch* Parent = nullptr;

	std::vector<Instruction*> Data = std::vector<Instruction*>();

	void Add(Instruction* ins) {
		Data.push_back(ins);
	}

	// void End();

	// td::string Compile(Generator* ignore = nullptr);
};