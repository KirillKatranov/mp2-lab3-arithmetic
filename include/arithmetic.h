// объявление функций и классов для вычисления арифметических выражений

#include <iostream>
#include "stack.h"

using namespace std;

enum LexemType { NUMBER, OPERATOR, VARIABLE, LBRACKET, RBRACKET, UNKNOWN };

struct Lexem
{
	char str[10];		// массив char под лексемы
	LexemType type;		// тип лексемы
	double Var;			// значение лексемы
	int Pr;				// приоритет лексемы

	Lexem() {}	// пустой конструктор 
	Lexem(char* s, int k);	// конструктор 

	Lexem(const Lexem & l);		// конструктор копирования
	Lexem operator=(const Lexem & l);	// перегрузка оператора =
	void SetVar();	// функция установки значения переменной
};

class arithmetic
{
	Lexem* pLexem;		// массив лексем
	int Size;			// размер массива
	int nLexems;		// количество лексем в массиве

public:
	arithmetic() {};		// пустой конструткор
	arithmetic(char* s);	// конструктор
	arithmetic(const arithmetic & a);		// конструктор копирования
	~arithmetic();		// деструктор

	int GetNLexems() { return nLexems; };		// возвращает количество лексем
	arithmetic PolishEntry();		// приведение к польской записи
	double CalculatePolishEntry();		// вычисление по польской записи
	arithmetic& operator +=(const Lexem a);			// перегрузка оператора +=
	arithmetic& operator =(const arithmetic & a);		// перегрузка оператора =
	char GetCharLexem(int n);		// возвращает поля char для лексемы

	bool CheckBracket();	// проверка скобок
	bool CheckLetters();	// проверка переменых
	bool CheckOperator();	// проверка операторов
	bool CheckPoint();		// проверка точек
};