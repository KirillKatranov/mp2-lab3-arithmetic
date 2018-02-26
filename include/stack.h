// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память

#include <iostream>

using namespace std;

// Шаблон стека

template <class ValType>
class Stack
{
protected:
	ValType *pStack; // массив ValType (может быть int, double и т.д.) 
	int Size;		// физический размер
	int Index;	// индекс первой свободной ячейки (следующая ячейка, после той, в которую установлен элемент)
public:
	Stack(int s = 10);
	Stack(const Stack &v);			// конструктор копирования
	~Stack();
	void Push(ValType elem);		// вставка элемента
	ValType Pop();		// удаление элемента
	ValType& Top();		// просмотр верхнего элемента (без удаления)
	bool IsEmpty();		// проверка на пустоту
	int GetSize() { return (Index + 1); }	// кол-во элементов в стеке
	void Clean();		// очистка стека

};

template <class ValType>
Stack<ValType>::Stack(int s)
{
	if (s<0)
		throw ("Error");
	Size = s;
	Index = -1;
	pStack = new ValType[Size];
} /*-------------------------------------------------------------------------*/

template <class ValType>
Stack<ValType>::Stack(const Stack<ValType> &v)
{
	Size = v.Size;
	Index = v.Index;
	pStack = new ValType[Size];
	for (int i = 0; i < Index; i++)
		pStack[i] = v.pStack[i];
} /*-------------------------------------------------------------------------*/

template <class ValType>
Stack<ValType>::~Stack()
{
	delete[] pStack;
} /*-------------------------------------------------------------------------*/

template <class ValType>
void Stack<ValType>::Push(ValType elem)
{
	if ((Size - Index) >= 1)
	{
		Index += 1;
		pStack[Index] = elem;
	}
	else
		if ((Size - Index) == 0)
		{
			ValType* pStackNew = new ValType[Size + 10];
			for (int i = 0; i < Index + 1; i++)
			{
				pStackNew[i] = pStack[i];
			}
			Index = Index + 1;
			pStackNew[Index] = elem;
			delete[] pStack;
			pStack = pStackNew;
			Size = Size + 10;

		}
} /*-------------------------------------------------------------------------*/

template <class ValType>
ValType Stack<ValType>::Pop()
{
	return pStack[Index--];
} /*-------------------------------------------------------------------------*/

template <class ValType>
ValType& Stack<ValType>::Top()
{
	return pStack[Index];
}  /*-------------------------------------------------------------------------*/

template <class ValType>
bool Stack<ValType>::IsEmpty()
{
	if (Index <0)
		return 1;
	else
		return 0;
} /*-------------------------------------------------------------------------*/

template <class ValType>
void  Stack<ValType>::Clean()
{
	Index = -1;
} /*-------------------------------------------------------------------------*/