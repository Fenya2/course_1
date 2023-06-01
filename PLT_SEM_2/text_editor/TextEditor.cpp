#include "TextEditor.h"
#include <string>
#include <sstream>

TextEditor::TextEditor()
{
	_text="";
	_undoStack=OpStack();
	_redoStack=OpStack();
	_isOpen=true;
}

TextEditor::~TextEditor(){}

void TextEditor::add(std::string entry,bool onRollback)
{
	if(!onRollback)
		_redoStack.clear();
	_text+=entry;
	opNode* node=new opNode(opCode::REMOVE, entry);
	_undoStack.push(node);
}

void TextEditor::remove(int qnt, bool onRollback)
{
	if(!onRollback)
		_redoStack.clear();
	if(qnt>_text.size())
		qnt=_text.size();
	std::string entry;
	entry=_text.substr(_text.size()-qnt,qnt);
	opNode* node=new opNode(opCode::ADD,entry);
	_text.resize(_text.size()-entry.size());
	_undoStack.push(node);
}

void TextEditor::undo()
{
	if(_undoStack.isEmpty())
		return;
	opNode* op=_undoStack.pop();
	_redoStack.push(reverseOperation(op));
	switch(op->code)
	{
		case opCode::ADD:
			add(op->operand,true);
			delete op;
			delete _undoStack.pop(); // костыль
			return;
		case opCode::REMOVE:
			remove(op->operand.size(),true);
			delete op;
			delete _undoStack.pop();
			return;
	}
}

void TextEditor::redo()
{
	if(_redoStack.isEmpty())
		return;
	opNode* op = _redoStack.pop();
	_undoStack.push(reverseOperation(op));
	switch(op->code)
	{
		case opCode::ADD:
			add(op->operand, true);
			delete op;
			delete _undoStack.pop();
			return;
		case opCode::REMOVE:
			remove(op->operand.size(),true);
			delete op;
			delete _undoStack.pop();
			return;
	}
}

std::string TextEditor::getText()
{return _text;}

opNode* TextEditor::reverseOperation(const opNode* op)
{
	opNode* node;
	switch(op->code)
	{
		case opCode::ADD:
			node=new opNode(opCode::REMOVE,op->operand);
			return node;
		case opCode::REMOVE:
			node=new opNode(opCode::ADD,op->operand);
			return node;
	}
	return nullptr;
}

void TextEditor::execute(std::string prompt)
{
	char command;
	std::string operand;
	std::stringstream ss;
	ss<<prompt;
	command=ss.get();
	ss.get();
	getline(ss,operand);
	switch(command)
	{
		case 'A':
		case 'a':
			add(operand,false);
			break;
		case 'D': 
		case 'd': 
			try
			{remove(std::stoi(operand),false);}
			catch(...){}
			break;
		case 'U':
		case 'u':
			try
			{
				for(int i=0;i<std::stoi(operand);++i)
					undo();
			}
			catch(...) {undo();}
			break;
		case 'R':
		case 'r':
			try
			{
				for(int i = 0; i < std::stoi(operand); ++i)
					redo();
			}
			catch(...) {redo();}
			break;
		case 'Q':
		case 'q':
			close();
	}
}

void TextEditor::close()
{_isOpen=false;}

bool TextEditor::isOpen()
{return _isOpen;}
