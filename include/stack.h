// ���������� � ���������� ���������� �����
// ���� ������������ ��������: 
// - ������� ��������, 
// - ���������� ��������, 
// - �������� �������� �������� (��� ��������)
// - �������� �� �������, 
// - ��������� ���������� ��������� � �����
// - ������� �����
// ��� ������� � ������ ���� ������ �������������� ������

#include <iostream>

using namespace std;

// ������ �����

template <class ValType>
class Stack
{
protected:
	ValType *pStack; // ������ ValType (����� ���� int, double � �.�.) 
	int Size;		// ���������� ������
	int Index;	// ������ ������ ��������� ������ (��������� ������, ����� ���, � ������� ���������� �������)
public:
	Stack(int s = 10);
	Stack(const Stack &v);			// ����������� �����������
	~Stack();
	void Push(ValType elem);		// ������� ��������
	ValType Pop();		// �������� ��������
	ValType& Top();		// �������� �������� �������� (��� ��������)
	bool IsEmpty();		// �������� �� �������
	int GetSize() { return (Index + 1); }	// ���-�� ��������� � �����
	void Clean();		// ������� �����

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