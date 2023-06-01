#include <string>

enum class opCode
{
	ADD,
	REMOVE,
	UNDO,
	REDO,
	QUIT,
};

struct opNode
{
	opNode(opCode, std::string);
	~opNode();
	opCode code;
	std::string operand;
	opNode* next;
	std::string toString();
};

class OpStack
{
public: 
	OpStack();
	~OpStack();
	void push(opNode*);
	opNode* pop();
	opNode* seek();
	bool isEmpty();
	std::string toString();
	void clear();
private:
	opNode* _head;
};

class TextEditor
{
public:
	TextEditor();
	~TextEditor();
	void execute(std::string);
	void add(std::string, bool);
	void remove(int, bool);
	void undo();
	void redo();
	void close();
	bool isOpen();
	std::string getText();
private:
	bool _isOpen;
	std::string _text;
	OpStack _undoStack;
	OpStack _redoStack;
	opNode* reverseOperation(const opNode*);
};
