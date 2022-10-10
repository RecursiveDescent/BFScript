#include "../include/framework.hpp"

Instruction* Goto::Compile(Generator* gen, int* cptr, std::string& output) {
	int pos = *cptr;

	/*if (! relative) {
		Refresh();

		pos = Analyzer.Pointer;
	}*/

	bool higher = pos - Target < 0;

	int dist = abs(pos - Target);

	// Indent();

	// Output += "Goto " + std::to_string(cell) + "\n";

	// Indent();
	
	output += gen->Indent() + "Goto " + std::to_string(Target) + ":\n" + gen->Indent() + '\t';

	for (int i = 0; i < dist; i++) {
		output += higher ? '>' : '<';
	}

	output += "\n";

	return this;
}

Goto::Goto(Branch* owner, int target) {
	Owner = owner;
	
	Target = target;
}

void Set::Simulate(Generator* gen, int* cptr, bool memory) {
	*cptr = Target;

	if (memory)
		gen->Set(Target, Value);
}

Instruction* Set::Compile(Generator* gen, int* cptr, std::string& output) {
	Goto(Owner, Target).Compile(gen, cptr, output);

	output += gen->Indent() + "Set " + std::to_string(Target) + " = " + std::to_string(Value) + ":\n";

	gen->IndentLevel++;

	output += gen->Indent() + "[-Clear]\n" + gen->Indent();

	for (int i = 0; i < Value; i++) {
		output += '+';
	}

	output += '\n';

	gen->IndentLevel--;

	return this;
}

void Copy::Simulate(Generator* gen, int* cptr, bool memory) {
	*cptr = Temp;

	if (memory) {
		gen->Set(Target, gen->Cells[Source]);

		gen->Set(Temp, 0);

		gen->Set(Source, gen->Cells[Source]);
	}
}

Instruction* Copy::Compile(Generator* gen, int* cptr, std::string& output) {
	output += gen->Indent() + "Copy " + std::to_string(Target) + " = Cell " + std::to_string(Source) + ":\n";

	gen->IndentLevel++;

	Goto(Owner, Source).Compile(gen, cptr, output)->Simulate(gen, cptr);

	// Move to temp
	
	output += gen->Indent() + "[\n";

		output += gen->Indent() + "-\n";
	
		Goto(Owner, Temp).Compile(gen, cptr, output)->Simulate(gen, cptr);
	
		output += gen->Indent() + "+\n";

		Goto(Owner, Source).Compile(gen, cptr, output)->Simulate(gen, cptr);

	output += gen->Indent() + "]\n";

	// Move value from temp to both original cell and new cell

	Goto(Owner, Temp).Compile(gen, cptr, output)->Simulate(gen, cptr);

	output += gen->Indent() + "[\n";

	// Temp--

	output += gen->Indent() + "-\n";

	// Source++ Target++

	Goto(Owner, Source).Compile(gen, cptr, output)->Simulate(gen, cptr);

	output += gen->Indent() + "+\n";

	Goto(Owner, Target).Compile(gen, cptr, output)->Simulate(gen, cptr);

	output += gen->Indent() + "+\n";

	// Next loop
	
	Goto(Owner, Temp).Compile(gen, cptr, output)->Simulate(gen, cptr);

	output += gen->Indent() + "]\n";

	gen->IndentLevel--;

	return this;
}

void Move::Simulate(Generator* gen, int* cptr, bool memory) {
	*cptr = Source;

	if (memory) {
		gen->Set(Target, gen->Cells[Source]);

		gen->Set(Source, 0);
	}
}

Instruction* Move::Compile(Generator* gen, int* cptr, std::string& output) {
	output += gen->Indent() + "Move " + std::to_string(Target) + " = Cell " + std::to_string(Source) + ":\n";

	gen->IndentLevel++;

	Goto(Owner, Source).Compile(gen, cptr, output)->Simulate(gen, cptr);

	output += gen->Indent() + "[\n";

	Goto(Owner, Source).Compile(gen, cptr, output)->Simulate(gen, cptr);

	output += gen->Indent() + "-\n";

	Goto(Owner, Target).Compile(gen, cptr, output)->Simulate(gen, cptr);

	output += gen->Indent() + "+\n";

	Goto(Owner, Source).Compile(gen, cptr, output)->Simulate(gen, cptr);

	output += gen->Indent() + "]\n";

	gen->IndentLevel--;

	return this;
}

void Add::Simulate(Generator* gen, int* cptr, bool memory) {
	*cptr = B;

	if (memory) {
		gen->Set(A, gen->Cells[A] + gen->Cells[B]);

		gen->Set(B, 0);
	}
}

Instruction* Add::Compile(Generator* gen, int* cptr, std::string& output) {
	Goto(Owner, B).Compile(gen, cptr, output)->Simulate(gen, cptr);

	int aval = gen->Cells[A];

	int bval = gen->Cells[B];

	output += gen->Indent() + "Add " + std::to_string(A) + " = " + std::to_string(A) + " plus " + std::to_string(B) + ":\n";

	gen->IndentLevel++;

	output += gen->Indent() + "[-\n";
	
	gen->IndentLevel++;

	Goto(Owner, A).Compile(gen, cptr, output)->Simulate(gen, cptr);

	output += "+\n";

	Goto(Owner, B).Compile(gen, cptr, output)->Simulate(gen, cptr);

	gen->IndentLevel--;

	output += gen->Indent() + "]\n";

	gen->IndentLevel--;

	return this;
}

void Sub::Simulate(Generator* gen, int* cptr, bool memory) {
	*cptr = B;

	if (memory) {
		gen->Set(A, gen->Cells[A] - gen->Cells[B]);

		gen->Set(B, 0);
	}
}

Instruction* Sub::Compile(Generator* gen, int* cptr, std::string& output) {
	Goto(Owner, B).Compile(gen, cptr, output)->Simulate(gen, cptr);

	int aval = gen->Cells[A];

	int bval = gen->Cells[B];

	int ptr = *cptr;

	output += gen->Indent() + "Sub " + std::to_string(A) + " = " + std::to_string(A) + " minus " + std::to_string(B) + ":\n";

	gen->IndentLevel++;

	output += gen->Indent() + "[-\n";
	
	gen->IndentLevel++;

	Goto(Owner, A).Compile(gen, cptr, output)->Simulate(gen, cptr);

	output += gen->Indent() + "-\n";

	Goto(Owner, B).Compile(gen, cptr, output)->Simulate(gen, cptr);

	gen->IndentLevel--;

	output += gen->Indent() + "]\n";

	gen->IndentLevel--;

	return this;
}

void Mul::Simulate(Generator* gen, int* cptr, bool memory) {
	*cptr = B;

	if (memory) {
		gen->Set(A, gen->Cells[A] * gen->Cells[B]);
	
		gen->Set(B, 0);
	}
}

Instruction* Mul::Compile(Generator* gen, int* cptr, std::string& output) {
	Goto(Owner, A).Compile(gen, cptr, output)->Simulate(gen, cptr);

	output += "[-Clear]\n";
	
	Goto(Owner, B).Compile(gen, cptr, output)->Simulate(gen, cptr);

	int aval = gen->Cells[A];

	int bval = gen->Cells[B];

	output += gen->Indent() + "Mul " + std::to_string(A) + " = " + std::to_string(A) + " times " + std::to_string(B) + ":\n";

	gen->IndentLevel++;

	output += gen->Indent() + "[-\n";
	
	gen->IndentLevel++;
	
	output += gen->Indent();

	Goto(Owner, A).Compile(gen, cptr, output)->Simulate(gen, cptr);

	for (int i = 0; i < aval; i++) {
		output += '+';
	}

	output += '\n';

	Goto(Owner, B).Compile(gen, cptr, output)->Simulate(gen, cptr);

	gen->IndentLevel--;

	output += gen->Indent() + "]\n";

	gen->IndentLevel--;

	return this;
}

void Div::Simulate(Generator* gen, int* cptr, bool memory) {
	/*Interpreter analyzer = gen->Analyzer;

	Interpreter tmp = Interpreter();

	tmp.Cells = std::vector<int>(analyzer.Cells);

	tmp.Pointer = analyzer.Pointer;

	gen->Analyzer = tmp;

	std::string str = "";

	this->Compile(gen, cptr, str);

	tmp.Run(str);

	if (! memory) {
		gen->Analyzer = analyzer;
	}
	else {
		
	}*/

	if ((A > Location && A < Location + 6) || (B > Location && B < Location + 6)) {
		std::cout << "Division cells can't be in the division workspace.\n";

		throw new std::exception();
	}

	for (int i = 0; i < 6; i++) {
		gen->Set(Location + i, 0);
	}

	gen->Set(Location + 1, gen->Cells[A] % gen->Cells[B]);

	gen->Set(Location + 5, gen->Cells[A] / gen->Cells[B]);
}

Instruction* Div::Compile(Generator* gen, int* cptr, std::string& output) {
	std::cout << "A: " << gen->Cells[A] << "\n\n";

	std::cout << "B: " << gen->Cells[B] << "\n\n";
	
	(new Move(gen->Layout, Location, A))->Compile(gen, cptr, output);

	(new Move(gen->Layout, Location + 4, B))->Compile(gen, cptr, output);
	
	Goto(Owner, Location).Compile(gen, cptr, output)->Simulate(gen, cptr);

	output += gen->Indent() + "Div " + std::to_string(A) + " divided by " + std::to_string(B) + ":\n";

	gen->IndentLevel++;

	output += gen->Indent() + "[->+>>+>-[<-]<[<<[->>>+<<<]>>>>+<<-<]<<]\n";

	gen->IndentLevel--;

	return this;
}

void Compare::Simulate(Generator* gen, int* cptr, bool memory) {
	*cptr = A;

	if (memory) {
		gen->Set(B, gen->Cells[A] != gen->Cells[B]);

		gen->Set(A, 0);
	}
}

// Remember that it sets the result to 0 for equal and 1 for not equal
Instruction* Compare::Compile(Generator* gen, int* cptr, std::string& output) {
	int aval = gen->Cells[A];

	int bval = gen->Cells[B];

	int ptr = *cptr;

	output += gen->Indent() + "Compare " + std::to_string(B) + " = " + std::to_string(A) + " != " + std::to_string(B) + ":\n";

	gen->IndentLevel++;

	Goto(Owner, B).Compile(gen, &ptr, output)->Simulate(gen, &ptr);

	Sub(Owner, A, B).Compile(gen, &ptr, output)->Simulate(gen, &ptr);

	Goto(Owner, A).Compile(gen, &ptr, output)->Simulate(gen, &ptr);

	output += '\n' + gen->Indent() + "[\n";

	gen->IndentLevel++;

	output += gen->Indent() + "-\n";

	Goto(Owner, B).Compile(gen, &ptr, output)->Simulate(gen, &ptr);

	output += gen->Indent() + "+\n";

	Goto(Owner, A).Compile(gen, &ptr, output)->Simulate(gen, &ptr);

	output += gen->Indent() + "[-]\n";

	gen->IndentLevel--;

	output += gen->Indent() + "]\n";

	gen->IndentLevel--;

	return this;
}

// Destroys cell to right
void Negate::Simulate(Generator* gen, int* cptr, bool memory) {
	*cptr = A;

	if (memory) {
		if (gen->Cells[A] != 0)
			gen->Set(A, 0);
		else
			gen->Set(A, 1);

		gen->Set(A + 1, 0);
	}
}

Instruction* Negate::Compile(Generator* gen, int* cptr, std::string& output) {
	int aval = gen->Cells[A];

	output += gen->Indent() + "Negate " + std::to_string(A) + " (Destroys cell to the right):\n";

	gen->IndentLevel++;

	int ptr = *cptr;
	
	Goto(Owner, A + 1).Compile(gen, cptr, output)->Simulate(gen, cptr);

	output += gen->Indent() + "[-]\n";

	output += gen->Indent() + "<[->+<]+\n";

	output += gen->Indent() + ">[-<->]<\n";

	gen->IndentLevel--;

	return this;
}

void If::Simulate(Generator* gen, int* cptr, bool memory) {
	*cptr = Condition;

	if (memory)
		gen->Set(Condition, 0);
}

Instruction* If::Compile(Generator* gen, int* cptr, std::string& output) {
	int ptr = *cptr;
	
	Goto(Owner, Condition).Compile(gen, &ptr, output)->Simulate(gen, cptr);

	output += gen->Indent() + "If " + std::to_string(Condition) + ":\n";

	output += gen->Indent() + "[\n";

	gen->IndentLevel++;

	std::cout << "Wow: " << (int) gen->Cells[Condition] << "\n\n";

	for (Instruction* ins : Br->Data) {
		if (gen->Cells[Condition] != 0)
			ins->Compile(gen, cptr, output)->Simulate(gen, cptr, true);
		else
			ins->Compile(gen, cptr, output)->Simulate(gen, cptr);

		/*if (gen->Cells[Condition])
			ins->Simulate(gen, &gen->Cell);*/
	}

	//									&ptr?
	Goto(Owner, Condition).Compile(gen, cptr, output)->Simulate(gen, cptr);

	output += gen->Indent() + "[-Clear]\n";

	gen->IndentLevel--;
	
	output += gen->Indent() + "]\n";

	return this;
}

Instruction* Output::Compile(Generator* gen, int* cptr, std::string& output) {
	Goto(Owner, A).Compile(gen, cptr, output)->Simulate(gen, cptr);
	
	output += gen->Indent() + "Output <" + std::to_string(A) + "> .";

	return this;
}

std::string Generator::Indent() {
	std::string indent = "";

	for (int i = 0; i < IndentLevel; i++) {
		 indent += '\t';
	}

	return indent;
}

std::string Generator::Compile() {
	std::string result = "";

	for (Instruction* ins : Layout->Data) {
		ins->Compile(this, &Cell, result);

		ins->Simulate(this, &Cell, true);
	}

	return result;
}

void Generator::Set(int cell, int value) {

	/*if (Cells.size() > 2)
		std::cout << "BEFVAL: " << Cells[2] << "\n\n";*/
	
	if (cell >= Cells.size()) {
		for (int i = 0; i <= cell - Cells.size() + 3; i++) {
			Cells.push_back(0);
		}
	}

	// std::cout << "VAL: " << Cells.at(2) << "\n\n";

	Cells[cell] = value;
}

Generator::Generator() {
	Layout = new Branch();
}