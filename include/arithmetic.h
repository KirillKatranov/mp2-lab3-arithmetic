// ���������� ������� � ������� ��� ���������� �������������� ���������

#include <iostream>
#include "stack.h"

using namespace std;

enum LexemType { NUMBER, OPERATOR, VARIABLE, LBRACKET, RBRACKET, UNKNOWN };

struct Lexem
{
	char str[10];		// ������ char ��� �������
	LexemType type;		// ��� �������
	double Var;			// �������� �������
	int Pr;				// ��������� �������

	Lexem() {}	// ������ ����������� 
	Lexem(char* s, int k);	// ����������� 

	Lexem(const Lexem & l);		// ����������� �����������
	Lexem operator=(const Lexem & l);	// ���������� ��������� =
	void SetVar();	// ������� ��������� �������� ����������
};

class arithmetic
{
	Lexem* pLexem;		// ������ ������
	int Size;			// ������ �������
	int nLexems;		// ���������� ������ � �������

public:
	arithmetic() {};		// ������ �����������
	arithmetic(char* s);	// �����������
	arithmetic(const arithmetic & a);		// ����������� �����������
	~arithmetic();		// ����������

	int GetNLexems() { return nLexems; };		// ���������� ���������� ������
	arithmetic PolishEntry();		// ���������� � �������� ������
	double CalculatePolishEntry();		// ���������� �� �������� ������
	arithmetic& operator +=(const Lexem a);			// ���������� ��������� +=
	arithmetic& operator =(const arithmetic & a);		// ���������� ��������� =
	char GetCharLexem(int n);		// ���������� ���� char ��� �������

	bool CheckBracket();	// �������� ������
	bool CheckLetters();	// �������� ���������
	bool CheckOperator();	// �������� ����������
	bool CheckPoint();		// �������� �����
};