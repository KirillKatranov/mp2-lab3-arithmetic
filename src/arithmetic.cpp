// реализация функций и классов для вычисления арифметических выражений
#include "arithmetic.h"

Lexem::Lexem(char* s, int k)
{
	strncpy(str, s, k);
	str[k] = '\0';

	if (k == 1)
	{
		if (isalpha(str[0]))
			type = VARIABLE;
		else
			if (isdigit(str[0]))
			{
				type = NUMBER;
				Var = atof(str);
			}
			else
			{
				switch (str[0])
				{
				case '(': type = LBRACKET;
					Pr = 0;
					break;
				case ')': type = RBRACKET;
					break;
				case '+': type = OPERATOR;
					Pr = 1;
					break;
				case '-': type = OPERATOR;
					Pr = 1;
					break;
				case '*': type = OPERATOR;
					Pr = 2;
					break;
				case '/': type = OPERATOR;
					Pr = 2;
					break;
				default: type = UNKNOWN;
					break;
				}
			}
	}
	else if (k != 1)
	{
		type = NUMBER;
		Var = atof(str);
	}
}

Lexem::Lexem(const Lexem & l)
{
	strcpy(str, l.str);

	type = l.type;
	Var = l.Var;
	Pr = l.Pr;
}

Lexem Lexem::operator=(const Lexem & l)
{
	strcpy(str, l.str);

	type = l.type;
	Var = l.Var;
	Pr = l.Pr;

	return *this;
}

void Lexem::SetVar()
{
	setlocale(LC_ALL, "Russian");

	cout << "Введите значение переменной " << str[0] << " : ";
	cin >> Var;
	cout << endl;
}

arithmetic::arithmetic(char* s)
{
	Size = strlen(s);
	int k = 0; // счетчик лексем
	pLexem = new Lexem[Size];
	for (int i = 0; i < Size; i++)
	{
		if (isdigit(s[i]))
		{
			int j = i; // конец числа
			while (isdigit(s[j]) || (s[j] == ','))
			{
				if (s[j] != '/0')
					j++;
			}
			pLexem[k] = Lexem(s + i, j - i);
			k++;
			i = j - 1;
		}
		else
		{
			pLexem[k] = Lexem(s + i, 1);
			k++;
		}
	}
	nLexems = k;

	for (int i = 0; i < nLexems; i++)
	{
		if (pLexem[i].type == VARIABLE)
		{
			pLexem[i].SetVar();
			for (int j = i + 1; j< nLexems; j++)
			{
				if (pLexem[i].str[0] == pLexem[j].str[0])
				{
					pLexem[j].Var = pLexem[i].Var;
					pLexem[j].type = NUMBER;
				}
			}
			pLexem[i].type = NUMBER;
		}
	}

	for (int i = 0; i < nLexems - 3; i++)
	{
		if ((pLexem[i].type == LBRACKET) && (pLexem[i + 1].str[0] == '-') && (pLexem[i + 2].type == NUMBER))
		{
			pLexem[i + 2].Var = 0 - pLexem[i + 2].Var;
			for (int j = i + 1; j < nLexems - 1; j++)
			{
				pLexem[j] = pLexem[j + 1];
			}
			nLexems--;
		}
	}

	for (int i = 0; i < 1; i++)
	{
		if ((pLexem[i].str[0] == '-') && (pLexem[i + 1].type == NUMBER))
		{

			pLexem[i + 1].Var = 0 - pLexem[i + 1].Var;
			for (int j = i; j < nLexems - 1; j++)
			{
				pLexem[j] = pLexem[j + 1];
			}
			nLexems--;
		}
	}

	for (int i = 0; i < nLexems - 3; i++)
	{
		if ((pLexem[i].type == LBRACKET) && (pLexem[i + 1].str[0] == '-') && (pLexem[i + 2].type == VARIABLE))
		{
			pLexem[i + 2].SetVar();
			pLexem[i + 2].type = NUMBER;
			pLexem[i + 2].Var = 0 - pLexem[i + 2].Var;
			for (int j = i + 1; j < nLexems - 1; j++)
			{
				pLexem[j] = pLexem[j + 1];
			}
			nLexems--;
		}
	}

	for (int i = 0; i < 1; i++)
	{
		if ((pLexem[i].str[0] == '-') && (pLexem[i + 1].type == VARIABLE))
		{
			pLexem[i + 1].SetVar();
			pLexem[i + 1].type = NUMBER;
			pLexem[i + 1].Var = 0 - pLexem[i + 1].Var;
			for (int j = i; j < nLexems - 1; j++)
			{
				pLexem[j] = pLexem[j + 1];
			}
			nLexems--;
		}
	}
}

arithmetic::arithmetic(const arithmetic & a)
{
	Size = a.Size;
	nLexems = a.nLexems;

	pLexem = new Lexem[Size];
	for (int i = 0; i < nLexems; i++)
		pLexem[i] = a.pLexem[i];

}

arithmetic::~arithmetic()
{
	delete[] pLexem;
}

arithmetic& arithmetic::operator +=(const Lexem a)
{
	int size = this->GetNLexems();
	pLexem[size] = a;
	nLexems += 1;

	return *this;
}

arithmetic& arithmetic::operator =(const arithmetic & a)
{
	Size = a.Size;
	nLexems = a.nLexems;

	pLexem = new Lexem[Size];
	for (int i = 0; i < nLexems; i++)
		pLexem[i] = a.pLexem[i];

	return (*this);
}

arithmetic arithmetic::PolishEntry()
{
	arithmetic res(*this);
	res.nLexems = 0;
	Stack<Lexem> s1;
	int k = 0;

	for (int i = 0; i < nLexems; i++)
	{
		if ((pLexem[i].type == NUMBER) || (pLexem[i].type == VARIABLE))
			res += pLexem[i];

		if (pLexem[i].type == LBRACKET)
		{
			s1.Push(pLexem[i]);
		}

		if (pLexem[i].type == OPERATOR)
		{
			if (s1.IsEmpty())
				s1.Push(pLexem[i]);
			else
			{
				Lexem x = s1.Top();
				while ((s1.IsEmpty() != 1) && (x.Pr >= pLexem[i].Pr))
				{
					x = s1.Pop();
					res += x;
					x = s1.Top();
				}
				s1.Push(pLexem[i]);
			}
		}

		if (pLexem[i].type == RBRACKET)
		{
			Lexem x = s1.Pop();
			while (x.type != LBRACKET)
			{
				res += x;
				x = s1.Pop();
			}
		}
	}

	while (!s1.IsEmpty())
	{
		Lexem x = s1.Pop();
		res += x;
	}

	return res;
}

double arithmetic::CalculatePolishEntry()
{
	/*for (int i = 0; i < nLexems; i++)
	{
	if (pLexem[i].type == VARIABLE)
	{
	pLexem[i].SetVar();
	for(int j=i+1; j< nLexems; j++)
	{
	if(pLexem[i].str[0] == pLexem[j].str[0])
	{
	pLexem[j].Var = pLexem[i].Var;
	pLexem[j].type = NUMBER;
	}
	}
	pLexem[i].type = NUMBER;
	}
	}*/

	Stack<double> s1;
	double res = 0.0;

	for (int i = 0; i < nLexems; i++)
	{
		if (pLexem[i].type == NUMBER)
		{
			s1.Push(pLexem[i].Var);
		}

		if (pLexem[i].type == OPERATOR)
		{
			double A = s1.Pop();
			double B = s1.Pop();

			switch (pLexem[i].str[0])
			{
			case '+':
				res = A + B;
				break;
			case '-':
				res = B - A;
				break;
			case '*':
				res = A * B;
				break;
			case '/':
				res = B / A;
				break;
			}
			s1.Push(res);
		}
	}
	return s1.Pop();
}

bool arithmetic::CheckBracket()
{
	setlocale(LC_ALL, "Russian");

	int tmp = 0;

	for (int i = 0; i < nLexems; i++)
	{
		if (pLexem[i].type == LBRACKET)
			tmp++;

		if (pLexem[i].type == RBRACKET)
			tmp--;
	}

	if (tmp != 0)
	{
		cout << " Ошибка. Неправильное количество скобок." << endl;
		return 0;
	}
	else
	{
		return 1;
	}
}

bool arithmetic::CheckLetters()
{
	setlocale(LC_ALL, "Russian");

	int check = 0;
	for (int i = 0; i < nLexems; i++)
	{
		if (pLexem[i].type == UNKNOWN)
		{
			cout << " Ошибка. Недопустимый символ. " << endl;
			check++;
		}
	}

	for (int i = 0; i < nLexems - 1; i++)
	{
		if ((pLexem[i].type == VARIABLE) && (pLexem[i + 1].type == VARIABLE))
		{
			int k = 1;
			for (int j = i + 2; j < nLexems - 1; j++)
			{
				if (pLexem[j].type != VARIABLE)
				{
					j = nLexems;
				}
				k++;
			}
			cout << " Ошибка. Недопустимое имя переменной. " << endl;
			i = i + k;
			check++;
		}
	}

	if (check != 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

bool arithmetic::CheckOperator()
{
	setlocale(LC_ALL, "Russian");

	int check = 0;
	for (int i = 1; i < nLexems; i++)
	{
		if ((pLexem[i].type == OPERATOR) && (pLexem[i - 1].type == OPERATOR))
		{
			cout << " Ошибка. Несколько операций подряд. " << endl;
			check++;
		}
	}

	{
		int n = 0;
		int m = 0;

		for (int i = 0; i < nLexems; i++)
		{
			if (pLexem[i].type == OPERATOR)
			{
				n++;
			}
			if ((pLexem[i].type == VARIABLE) || (pLexem[i].type == NUMBER))
			{
				m++;
			}
		}
		if (n > m - 1)
		{
			cout << " Ошибка. Неверное количество операций. " << endl;
			check++;
		}
	}

	for (int i = 1; i < nLexems; i++)
	{
		if ((pLexem[i].type == RBRACKET) && (pLexem[i - 1].type == OPERATOR))
		{
			cout << " Ошибка. Знак операции перед ')'. " << endl;
			check++;
		}

	}

	if ((pLexem[nLexems - 1].type == RBRACKET) && (pLexem[nLexems].type == OPERATOR))
	{
		cout << " Ошибка. Знак операции после ')' в конце выражения. " << endl;
		check++;
	}


	for (int i = 1; i < nLexems; i++)
	{
		if ((pLexem[i - 1].type == LBRACKET) && (pLexem[i].type == OPERATOR))
		{
			cout << " Ошибка. Знак операции после '('. " << endl;
			check++;
		}
	}

	if ((pLexem[1].type == LBRACKET) && (pLexem[0].type == OPERATOR))
	{
		cout << " Ошибка. Знак операции перед '(' в начале выражения. " << endl;
		check++;
	}

	if (check != 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

bool arithmetic::CheckPoint()
{
	setlocale(LC_ALL, "Russian");

	int check = 0;
	for (int i = 1; i < nLexems; i++)
	{
		if ((pLexem[i].type == VARIABLE) && (pLexem[i - 1].str[0] == ','))
		{
			cout << " Ошибка. Запятая находится перед переменной. " << endl;
			check++;
		}

		if ((pLexem[i - 1].type == VARIABLE) && (pLexem[i].str[0] == ','))
		{
			cout << " Ошибка. Запятая находится после переменной. " << endl;
			check++;
		}
	}

	for (int i = 1; i < nLexems; i++)
	{
		if ((pLexem[i].type == RBRACKET) && (pLexem[i - 1].str[0] == ','))
		{
			cout << " Ошибка. Запятая находится перед ')' " << endl;
			check++;
		}
	}

	for (int i = 0; i < nLexems - 1; i++)
	{
		if ((pLexem[i].type == RBRACKET) && (pLexem[i + 1].str[0] == ','))
		{
			cout << " Ошибка. Запятая находится после ')' " << endl;
			check++;
		}
	}

	for (int i = 1; i < nLexems; i++)
	{
		if ((pLexem[i].type == LBRACKET) && (pLexem[i - 1].str[0] == ','))
		{
			cout << " Ошибка. Запятая находится перед '(' " << endl;
			check++;
		}
	}

	for (int i = 0; i < nLexems - 1; i++)
	{
		if ((pLexem[i].type == LBRACKET) && (pLexem[i + 1].str[0] == ','))
		{
			cout << " Ошибка. Запятая находится после '(' " << endl;
			check++;
		}
	}

	if (check != 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

char arithmetic::GetCharLexem(int n)
{
	char res;
	res = pLexem[n].str[0];
	return res;
}