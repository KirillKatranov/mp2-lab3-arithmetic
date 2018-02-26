// тесты для вычисления арифметических выражений

#include <gtest.h>
#include "arithmetic.h"

TEST(arithmetic, can_get_nlexems)
{
	arithmetic tmp("50/5*2-19");
	int a = tmp.GetNLexems();

	EXPECT_EQ(7, a);
}

TEST(arithmetic, can_make_up_polish_entry)
{
	arithmetic tmp("(5*5+5)/(2*3)");
	tmp = tmp.PolishEntry();

	char tmp2[9];
	tmp2[0] = '5';
	tmp2[1] = '5';
	tmp2[2] = '*';
	tmp2[3] = '5';
	tmp2[4] = '+';
	tmp2[5] = '2';
	tmp2[6] = '3';
	tmp2[7] = '*';
	tmp2[8] = '/';

	bool res = true;
	for (int i = 0; i < 9; i++)
		if (tmp2[i] != tmp.GetCharLexem(i))
			res = false;

	EXPECT_EQ(true, res);
}

TEST(arithmetic, can_copied_arithmetic)
{
	arithmetic tmp("(5*1+7)");
	arithmetic tmp2(tmp);

	char tmp3[7];
	tmp3[0] = '(';
	tmp3[1] = '5';
	tmp3[2] = '*';
	tmp3[3] = '1';
	tmp3[4] = '+';
	tmp3[5] = '7';
	tmp3[6] = ')';

	bool res = true;
	for (int i = 0; i < 7; i++)
		if (tmp3[i] != tmp2.GetCharLexem(i))
			res = false;

	EXPECT_EQ(true, res);
}

TEST(arithmetic, can_calculate_polish_entry)
{
	arithmetic tmp("(8+2*5)/(1+3*2-4)");
	tmp = tmp.PolishEntry();
	double res = tmp.CalculatePolishEntry();

	EXPECT_EQ(6, res);
}

TEST(arithmetic, can_compare_two_arithmetic)
{
	arithmetic tmp("(8+2*5)/(1+3*2-4)");
	arithmetic tmp2("0");
	tmp2 = tmp;

	char tmp3[17];
	tmp3[0] = '(';
	tmp3[1] = '8';
	tmp3[2] = '+';
	tmp3[3] = '2';
	tmp3[4] = '*';
	tmp3[5] = '5';
	tmp3[6] = ')';
	tmp3[7] = '/';
	tmp3[8] = '(';
	tmp3[9] = '1';
	tmp3[10] = '+';
	tmp3[11] = '3';
	tmp3[12] = '*';
	tmp3[13] = '2';
	tmp3[14] = '-';
	tmp3[15] = '4';
	tmp3[16] = ')';

	bool res = true;
	for (int i = 0; i < 17; i++)
		if (tmp3[i] != tmp2.GetCharLexem(i))
			res = false;

	EXPECT_EQ(true, res);
}

TEST(arithmetic, can_check_false_number_bracket)
{
	arithmetic tmp("(()");

	bool res;

	res = tmp.CheckBracket();

	EXPECT_EQ(false, res);
}

TEST(arithmetic, can_check_true_number_bracket_in_expression)
{
	arithmetic tmp2("(4+5)");

	bool res2;

	res2 = tmp2.CheckBracket();

	EXPECT_EQ(true, res2);
}

TEST(arithmetic, can_check_true_number_bracket)
{
	arithmetic tmp3("()");

	bool res3;

	res3 = tmp3.CheckBracket();

	EXPECT_EQ(true, res3);
}

TEST(arithmetic, can_check_point_before_variable)
{
	arithmetic tmp(",a");
	bool res;
	res = tmp.CheckPoint();
	EXPECT_EQ(false, res);
}

TEST(arithmetic, can_check_point_after_variable)
{
	arithmetic tmp2("a,");
	bool res2;
	res2 = tmp2.CheckPoint();
	EXPECT_EQ(false, res2);
}

TEST(arithmetic, can_check_point_before_lbracket)
{
	arithmetic tmp3(",)");
	bool res3;
	res3 = tmp3.CheckPoint();
	EXPECT_EQ(false, res3);
}

TEST(arithmetic, can_check_point_after_lbracket)
{
	arithmetic tmp4("(,");
	bool res4;
	res4 = tmp4.CheckPoint();
	EXPECT_EQ(false, res4);
}

TEST(arithmetic, can_check_point_before_rbracket)
{
	arithmetic tmp5(",(");
	bool res5;
	res5 = tmp5.CheckPoint();
	EXPECT_EQ(false, res5);
}

TEST(arithmetic, can_check_point_after_rbracket)
{
	arithmetic tmp6("),");
	bool res6;
	res6 = tmp6.CheckPoint();
	EXPECT_EQ(false, res6);
}

TEST(arithmetic, can_check_two_operators_undermine)
{
	arithmetic tmp("++");
	bool res;
	res = tmp.CheckOperator();
	EXPECT_EQ(false, res);
}

TEST(arithmetic, can_check_false_quantity_operator)
{
	arithmetic tmp2("4+5+");
	bool res2;
	res2 = tmp2.CheckOperator();
	EXPECT_EQ(false, res2);
}

TEST(arithmetic, can_checky_operator_before_lbracket)
{
	arithmetic tmp3("+)");
	bool res3;
	res3 = tmp3.CheckOperator();
	EXPECT_EQ(false, res3);
}

TEST(arithmetic, can_checky_operator_after_rbracket)
{
	arithmetic tmp4(")+");
	bool res4;
	res4 = tmp4.CheckOperator();
	EXPECT_EQ(false, res4);
}

TEST(arithmetic, can_checky_operator_after_lbracket)
{
	arithmetic tmp5("(+");
	bool res5;
	res5 = tmp5.CheckOperator();
	EXPECT_EQ(false, res5);
}

TEST(arithmetic, can_checky_operator_before_rbracket)
{
	arithmetic tmp6("+(");
	bool res6;
	res6 = tmp6.CheckOperator();
	EXPECT_EQ(false, res6);
}

TEST(arithmetic, can_check_unknown_letters)
{
	arithmetic tmp("^");
	bool res;
	res = tmp.CheckLetters();
	EXPECT_EQ(false, res);
}

TEST(arithmetic, can_check_incorrect_letters)
{
	arithmetic tmp2("aaa");
	bool res2;
	res2 = tmp2.CheckLetters();
	EXPECT_EQ(false, res2);
}

TEST(arithmetic, can_correct_cout_unary_minus_at_begin_expression)
{
	arithmetic tmp("-4+5");
	int res;
	tmp = tmp.PolishEntry();
	res = tmp.CalculatePolishEntry();
	EXPECT_EQ(1, res);
}

TEST(arithmetic, can_correct_multiply_unary_minus_at_begin_expression)
{
	arithmetic tmp("-4*5");
	int res;
	tmp = tmp.PolishEntry();
	res = tmp.CalculatePolishEntry();
	EXPECT_EQ(-20, res);
}

TEST(arithmetic, can_correct_cout_unary_minus_in_bracket)
{
	arithmetic tmp("5+(-4)");
	int res;
	tmp = tmp.PolishEntry();
	res = tmp.CalculatePolishEntry();
	EXPECT_EQ(1, res);
}

TEST(arithmetic, can_correct_multiply_unary_minus_in_bracket)
{
	arithmetic tmp("5*(-4)");
	int res;
	tmp = tmp.PolishEntry();
	res = tmp.CalculatePolishEntry();
	EXPECT_EQ(-20, res);
}

TEST(arithmetic, can_correct_cout_double_number)
{
	arithmetic tmp("5,0+5,0");
	int res;
	tmp = tmp.PolishEntry();
	res = tmp.CalculatePolishEntry();
	EXPECT_EQ(10, res);
}

TEST(arithmetic, can_cout_equality_lexem)
{
	arithmetic tmp("(8+2*5)/(1+3*2-4)");
	Lexem cmp[2];
	cmp[0] = Lexem("-", OPERATOR);
	cmp[1] = Lexem("6", VARIABLE);
	tmp += cmp[0];
	tmp += cmp[1];

	int res;
	tmp = tmp.PolishEntry();
	res = tmp.CalculatePolishEntry();
	EXPECT_EQ(0, res);
}

TEST(arithmetic, can_correct_sub_double_number)
{
	arithmetic tmp("7,3-4,7");
	int res;
	tmp = tmp.PolishEntry();
	res = tmp.CalculatePolishEntry();
	EXPECT_EQ(2.6, res);
}