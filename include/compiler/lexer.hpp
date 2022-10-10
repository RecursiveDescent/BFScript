#include <string>
#include <vector>

using std::string;

class Token {
	void* Value;

	public:

	string Type;

	template <class T>
	T Convert() {
		return *((T*) Value);
	}

	template <class T>
	bool Compare(string type, T value) {
		return Type == type && *((T*) Value) == value;
	}

	// Makes a copy to avoid referencing stack memory.
	Token(string value, bool str = false) {
		Type = str ? "String" : "Ident";

		Value = new string(value);
	}

	Token(int value) {
		Type = "Integer";

		Value = new int[1] { value };
	}

	Token(string type, void* value) {
		Type = type;

		Value = value;
	}

	void Free() {
		if (Type == "String")
			delete (string*) Value;

		if (Type == "Integer")
			delete (int*) Value;
	}
};

class Lexer {
	public:

	string Source;

	int Position = 0;

	int Line = 1;
	int Column = 1;

	int LastLine;
	int LastColumn;
	int LastPosition;

	char Get() {
		if (Position >= Source.length())
			return '\0';

		Column++;

		if (Source[Position] == '\n') {
			Line++;
			Column = 1;
		}

		return Source[Position++];
	}

	char Peek() {
		if (Position >= Source.length())
			return '\0';

		if (Source[Position] < 0)
			return '\0';

		return Source[Position];
	}

	bool AtEnd() {
		SkipSpace(); SkipLines();
		
		return Position >= Source.length() || Peek() == '\0';
	}

	bool IsSpace(char c) {
		return c == ' ' || c == '\t' || c == '\r';
	}

	bool IsDigit(char c) {
		return c >= '0' && c <= '9';
	}

	bool IsAlpha(char c) {
		return (c >= 'a'  && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
	}

	bool IsOp(char c) {
		return c == '!' || c == '=' || c == '+' || c == '-' || c == '/' || c == '*' || c == '.' || c == '>' || c == '<' || c == '|' || c == '&';
	}

	void SkipSpace() {
		while (IsSpace(Peek())) {
			Get();
		}
	}

	void SkipLines() {
		SkipSpace();
		
		while (Peek() == '\n') {
			Get();
		}
	}

	string PositionStr() {
		return std::to_string(Line) + ":" + std::to_string(Column);
	}

	string GetIdent() {
		string text = "";

		while (IsAlpha(Peek()) || IsDigit(Peek())) {
			text += Get();
		}

		return text;
	}

	int GetInteger() {
		string text = "";

		while (IsDigit(Peek())) {
			text += Get();
		}

		return stoi(text);
	}

	Token GetToken() {
		LastPosition = Position;
		LastLine = Line;
		LastColumn = Column;

		SkipSpace();
		SkipLines();

		if (Peek() == '\0')
			return Token("EOF", nullptr);

		if ((Peek() == '\n') && Get())
			return Token("Newline", nullptr);

		if ((Peek() == ';') && Get())
			return Token("Semicolon", nullptr);

		if (Peek() == '/' && Source[Position + 1] == '/') {
			while (Peek() != '\n')
				Get();
			
			return GetToken();
		}

		if (IsDigit(Peek()))
			return Token(GetInteger());

		// Get() only called if the condition is true
		if (Peek() == '{' && Get())
			return Token("LCurly", nullptr);

		if (Peek() == '}' && Get())
			 return Token("RCurly", nullptr);

		if (Peek() == '[' && Get())
			return Token("LBracket", nullptr);

		if (Peek() == ']' && Get())
			 return Token("RBracket", nullptr);

		if (Peek() == '(' && Get())
			return Token("LParen", nullptr);

		if (Peek() == ')' && Get())
			return Token("RParen", nullptr);

		if (Peek() == ',' && Get())
			return Token("Comma", nullptr);

		if (Peek() == ':' && Get())
			return Token("Colon", nullptr);

		if (Peek() == '"' || Peek() == '\'') {
			char qoute = Get();

			string text = "";

			while (Peek() != qoute) {
				if (Peek() == '\\') {
					Get();

					if (Peek() == 'n') {
						text += '\n';

						Get();
						
						continue;
					}
					
					text += Get();
					
					continue;
				}

				text += Get();
			}

			Get();

			return Token(text, true);
		}

		if (IsOp(Peek())) {
			string op = "";

			while (IsOp(Peek())) {
				op += Get();
			}

			Token tok = Token(op);

			tok.Type = "Op";

			return tok;
		}

		return Token(GetIdent());
	}

	Token PeekToken(int count = 1) {
		int lp = Position;
		int ll = Line;
		int lc = Column;

		Token tok = GetToken();

		for (int i = 1; i < count; i++) {
			tok = GetToken();
		}

		LastPosition = lp;
		LastLine = ll;
		LastColumn = lc;

		Revert();

		return tok;
	}

	void Revert() {
		Position = LastPosition;
		Line = LastLine;
		Column = LastColumn;
	}

	Lexer(string src) {
		Source = src;
	}
};