#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrix<int> m(3);
	TDynamicMatrix<int> m1(m);
  EXPECT_EQ(m1,m);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m(3);
	TDynamicMatrix<int> m1(m);
	EXPECT_NE(&m1[0][0], &m[0][0]);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m(3);
	EXPECT_EQ(3, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m(3);
	m[0][0] = 10;
	int num = m[0][0];
	EXPECT_EQ(num, m[0][0]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m(3);
	
	ASSERT_ANY_THROW( m[-1][0]=4);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m(3);

	ASSERT_ANY_THROW(m[5][0] = 4);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m(3);
	TDynamicMatrix<int> m1(m);
	m = m;

	EXPECT_EQ(m1,m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> m(3);
	TDynamicMatrix<int> m1(3);
	m1 = m;

	EXPECT_EQ(m1, m);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> m(3);
	TDynamicMatrix<int> m1(100);
	m1 = m;

	EXPECT_EQ(m1.size(), m.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m(3);
	TDynamicMatrix<int> m1(100);
	m1 = m;

	EXPECT_EQ(m1, m);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> m(3);
	TDynamicMatrix<int> m1(m);
	

	EXPECT_EQ(true, m==m1);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m(3);


	EXPECT_EQ(true, m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m(3);
	TDynamicMatrix<int> m1(5);


	EXPECT_EQ(false, m1 == m);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m(3), m1(3), m2(3);
	m.fillMat(1);
	m1.fillMat(2);
	m2.fillMat(3);


	EXPECT_EQ(m2, m1+ m);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m(3), m1(10);
	m.fillMat(1);
	m1.fillMat(2);


	ASSERT_ANY_THROW( m1 + m);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> m(3), m1(3), m2(3);
	m.fillMat(3);
	m1.fillMat(2);
	m2.fillMat(1);


	EXPECT_EQ(m2, m-m1);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m(3), m1(10);
	m.fillMat(1);
	m1.fillMat(2);


	ASSERT_ANY_THROW(m1 - m);
}

