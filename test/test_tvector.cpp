#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> vec(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(vec));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
    TDynamicVector<int> v1(5);
    v1[0] = 2;
    TDynamicVector<int> v2(v1);

    EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
    TDynamicVector<int> v1(5);
    TDynamicVector<int> v2(v1);

    EXPECT_NE(&v1[0], &v2[0]);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> vec(4);

  EXPECT_EQ(4, vec.size());
}

TEST(TVector, can_get_start_index)
{
    TDynamicVector<int> vec(4, 2);

    EXPECT_EQ(2, vec.getStartInd());
}

TEST(TVector, can_set_and_get_element)
{
    TDynamicVector<int> vec(4);
    vec[0] = 4;

    EXPECT_EQ(4, vec[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
    TDynamicVector<int> vec(4);
    ASSERT_ANY_THROW(vec[-3] = 0);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
    TDynamicVector<int> vec(4);
    ASSERT_ANY_THROW(vec[MAX_VECTOR_SIZE+1] = 0);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
    TDynamicVector<int> vec1(4);
    TDynamicVector<int> vec2(vec1);
    vec1 = vec1;

    EXPECT_EQ(vec2, vec1);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
    TDynamicVector<int> vec1(4), vec2(4);
    vec1[0] = 4;
    vec2 = vec1;

    EXPECT_EQ(vec2, vec1);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
    TDynamicVector<int> vec1(4), vec2(3);
    vec1[0] = 4;
    vec2 = vec1;

    EXPECT_EQ(4, vec2.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
    TDynamicVector<int> vec1(4), vec2(3);
    vec1[0] = 4;
    vec2 = vec1;

    EXPECT_EQ(vec2, vec1);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
    TDynamicVector<int> vec1(4);
    vec1[0] = 4;
    TDynamicVector<int> vec2(vec1);

    EXPECT_EQ(true, vec1 == vec2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
    TDynamicVector<int> vec1(4);
    vec1[0] = 4;

    EXPECT_EQ(true, vec1 == vec1);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
    TDynamicVector<int> vec1(4);
    vec1[0] = 4;
    TDynamicVector<int> vec2(6);
    vec2[0] = 4;

    EXPECT_NE(vec1,vec2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
    TDynamicVector<int> vec1(4), vec2(4);
    vec1.fillVec(0);
    vec2 = vec1 + 4;
    for (int i = vec1.getStartInd(); i < vec1.size() + vec1.getStartInd(); i++)
        vec1[i] += 4;

    EXPECT_EQ(vec2, vec1);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
    TDynamicVector<int> vec1(4), vec2(4);
    vec1.fillVec(5);
    vec2 = vec1 -5;
    for (int i = vec1.getStartInd(); i < vec1.size() + vec1.getStartInd(); i++)
        vec1[i] -= 5;

    EXPECT_EQ(vec2, vec1);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
    TDynamicVector<int> vec1(4), vec2(4);
    vec1.fillVec(1);
    vec2 = vec1*5;
    for (int i = vec1.getStartInd(); i < vec1.size() + vec1.getStartInd(); i++)
        vec1[i] *= 5;

    EXPECT_EQ(vec2, vec1);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
    TDynamicVector<int> vec1(4), vec2(4),vec3(4);
    vec1.fillVec(1);
    vec2.fillVec(2);
    vec3.fillVec(3);
    

    EXPECT_EQ(vec3, vec2+vec1);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
    TDynamicVector<int> vec1(4), vec2(3);
    vec1.fillVec(1);
    vec2.fillVec(1);
   
    ASSERT_ANY_THROW(vec2 + vec1);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
    TDynamicVector<int> vec1(4), vec2(4), vec3(4);
    vec1.fillVec(1);
    vec2.fillVec(1);
    vec3.fillVec(0);


    EXPECT_EQ(vec3,vec1-vec2) ;
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
    TDynamicVector<int> vec1(4), vec2(3);
    vec1.fillVec(1);
    vec2.fillVec(1);

    ASSERT_ANY_THROW(vec2 - vec1);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
    TDynamicVector<int> vec1(4), vec2(4);
    vec1.fillVec(1);
    vec2.fillVec(2);
    


    EXPECT_EQ(8, vec1 * vec2);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
    TDynamicVector<int> vec1(4), vec2(3);
    vec1.fillVec(1);
    vec2.fillVec(1);

    ASSERT_ANY_THROW(vec2 * vec1);
}

