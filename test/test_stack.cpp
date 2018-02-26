// тесты для стека

#include "stack.h"
#include <gtest.h>

// ТИПИЗИРОВАННЫЕ ТЕСТЫ

// типизированный класс
template <class T>
class StackTest : public testing::Test {
protected:
	Stack<T> s1;
	Stack<T> s2;
	Stack<T> s3;

public:
	StackTest() : s1(5), s2(5), s3(10)
	{

		for (int i = 0; i < 5; i++)
			s1.Push((T)i);
		for (int i = 0; i < 5; i++)
			s2.Push((T)i);
		for (int i = 0; i < 10; i++)
			s3.Push((T)i);
	}

	virtual ~StackTest() {}

};

// список типов, которые хотим протестировать
typedef ::testing::Types<int, double, char> MyTypes;

// связываем класс и типы
TYPED_TEST_CASE(StackTest, MyTypes);

// тесты
TYPED_TEST(StackTest, can_create_stack)
{
	ASSERT_NO_THROW(s1);
}

TYPED_TEST(StackTest, can_create_stack_positive_index)
{
	ASSERT_NO_THROW(Stack<MyTypes> s1(1));
}

TYPED_TEST(StackTest, can_create_stack_negative_index)
{
	ASSERT_ANY_THROW(Stack<MyTypes> s1(-1));
}

TYPED_TEST(StackTest, can_create_copied_stack)
{
	Stack<MyTypes> s1(5);

	ASSERT_NO_THROW(Stack<MyTypes> s4(s1));
}

TYPED_TEST(StackTest, stack_is_empty)
{
	Stack<MyTypes> s1(5);

	EXPECT_EQ(1, s1.IsEmpty());
}

TYPED_TEST(StackTest, get_size_stack)
{
	Stack<MyTypes> s1(5);

	EXPECT_EQ(0, s1.GetSize());
}

TEST(StackTest, can_top_int_element)
{
	Stack<int> s1;
	s1.Push(4);

	EXPECT_EQ(4, s1.Top());
}

TEST(StackTest, can_top_double_element)
{
	Stack<double> s1;
	s1.Push(4.0);

	EXPECT_EQ(4.0, s1.Top());
}

TEST(StackTest, can_top_char_element)
{
	Stack<char> s1;
	s1.Push('4');

	EXPECT_EQ('4', s1.Top());
}

TEST(StackTest, can_pop_int_element)
{
	Stack<int> s1;
	s1.Push(4);

	EXPECT_EQ(4, s1.Pop());
}

TEST(StackTest, can_pop_double_element)
{
	Stack<double> s1;
	s1.Push(4.0);

	EXPECT_EQ(4.0, s1.Pop());
}

TEST(StackTest, can_pop_char_element)
{
	Stack<char> s1;
	s1.Push('4');

	EXPECT_EQ('4', s1.Pop());
}

TEST(StackTest, clean_int_stack)
{
	Stack<int> s1;
	for (int i = 0; i < 5; i++)
		s1.Push(i);

	s1.Clean();

	EXPECT_EQ(0, s1.GetSize());
}

TEST(StackTest, clean_double_stack)
{
	Stack<double> s1;
	for (double i = 0.0; i < 5; i++)
		s1.Push(i);

	s1.Clean();

	EXPECT_EQ(0, s1.GetSize());
}