#include "../src/BitArray.h"
#include <gtest/gtest.h>

// ConstructorTestSuite
TEST(ConstructorTestSuite, DefaultConstructor)
{
    BitArray bitarray;
    EXPECT_TRUE(bitarray.empty());
    EXPECT_EQ(bitarray.size(), 0);
    EXPECT_EQ(bitarray.to_string(), "");
}

TEST(ConstructorTestSuite, EmptyExplicitConstructor)
{
    BitArray bitarray(0);
    EXPECT_TRUE(bitarray.empty());
    EXPECT_EQ(bitarray.size(), 0);
    EXPECT_EQ(bitarray.to_string(), "");
}

TEST(ConstructorTestSuite, BadExplicitConstructor)
{
    EXPECT_THROW(BitArray bitarray(-1), std::length_error);
}

TEST(ConstructorTestSuite, DefaultExplicitConstructor)
{
    BitArray bitarray(5);
    EXPECT_FALSE(bitarray.empty());
    EXPECT_EQ(bitarray.size(), 5);
    EXPECT_EQ(bitarray.to_string(), "00000");
}

TEST(ConstructorTestSuite, ValueExplicitConstructor)
{
    unsigned long num = 29; // in binary 11101
    int length = 8;
    BitArray bitarray(length, num);
    EXPECT_FALSE(bitarray.empty());
    EXPECT_EQ(bitarray.size(), length);
    EXPECT_EQ(bitarray.to_string(), "11101000");
}

TEST(ConstructorTestSuite, MaxValueExplicitConstructor)
{
    unsigned long num = (unsigned long)-1;
    int length = sizeof(unsigned long) * 8;
    BitArray bitarray(length, num);

    EXPECT_FALSE(bitarray.empty());
    EXPECT_EQ(bitarray.size(), length);

    std::string byte_ones = "11111111";
    std::string four_byte_ones = byte_ones + byte_ones + byte_ones + byte_ones;
    EXPECT_EQ(bitarray.to_string(), four_byte_ones);
}

TEST(ConstructorTestSuite, CutValueExplicitConstructor)
{
    unsigned long num = 29; // in binary 11101
    int length = 4;
    BitArray bitarray(length, num);
    EXPECT_FALSE(bitarray.empty());
    EXPECT_EQ(bitarray.size(), length);
    EXPECT_EQ(bitarray.to_string(), "1110");
}

TEST(ConstructorTestSuite, EmptyCopyConstructor)
{
    BitArray bitarray;
    BitArray copy_bitarray(bitarray);

    EXPECT_TRUE(copy_bitarray.empty());
    EXPECT_EQ(copy_bitarray.size(), 0);
    EXPECT_EQ(copy_bitarray.to_string(), "");
}

TEST(ConstructorTestSuite, ExplicitCopyConstructor)
{
    BitArray bitarray(12, 1234);
    BitArray copy_bitarray(bitarray);

    EXPECT_FALSE(copy_bitarray.empty());
    EXPECT_EQ(copy_bitarray.size(), bitarray.size());
    EXPECT_EQ(copy_bitarray.to_string(), bitarray.to_string());
}

// AssignmentOperationsTestSuite
TEST(AssignmentOperationsTestSuite, SwapBothEmpty)
{
    BitArray a;
    BitArray b;
    a.swap(b);

    EXPECT_TRUE(a.empty());
    EXPECT_EQ(a.size(), 0);
    EXPECT_EQ(a.to_string(), "");

    EXPECT_TRUE(b.empty());
    EXPECT_EQ(b.size(), 0);
    EXPECT_EQ(b.to_string(), "");
}

TEST(AssignmentOperationsTestSuite, SwapEmpty)
{
    BitArray a(5, 0);
    BitArray b;
    a.swap(b);

    EXPECT_TRUE(a.empty());
    EXPECT_EQ(a.size(), 0);
    EXPECT_EQ(a.to_string(), "");

    EXPECT_FALSE(b.empty());
    EXPECT_EQ(b.size(), 5);
    EXPECT_EQ(b.to_string(), "00000");
}

TEST(AssignmentOperationsTestSuite, SwapNormal)
{
    BitArray a(5, 0); // "00000"
    BitArray b(7, 3); // "1100000"
    a.swap(b);

    EXPECT_FALSE(a.empty());
    EXPECT_EQ(a.size(), 7);
    EXPECT_EQ(a.to_string(), "1100000");

    EXPECT_FALSE(b.empty());
    EXPECT_EQ(b.size(), 5);
    EXPECT_EQ(b.to_string(), "00000");
}

TEST(AssignmentOperationsTestSuite, AssignEmptyToEmpty)
{
    BitArray a;
    BitArray b;
    a = b;

    EXPECT_TRUE(a.empty());
    EXPECT_EQ(a.size(), 0);
    EXPECT_EQ(a.to_string(), "");
}

TEST(AssignmentOperationsTestSuite, AssignEmptyToNotEmpty)
{
    BitArray a;
    BitArray b(4, 5); // "1010"
    a = b;

    EXPECT_FALSE(a.empty());
    EXPECT_EQ(a.size(), 4);
    EXPECT_EQ(a.to_string(), "1010");
}

TEST(AssignmentOperationsTestSuite, AssignNotEmptyToNotEmpty)
{
    BitArray a(16, 2222);
    BitArray b(4, 5); // "1010"
    a = b;

    EXPECT_FALSE(a.empty());
    EXPECT_EQ(a.size(), 4);
    EXPECT_EQ(a.to_string(), "1010");
}

TEST(AssignmentOperationsTestSuite, AssignNotEmptyToEmpty)
{
    BitArray a(16, 2222);
    BitArray b;
    a = b;

    EXPECT_TRUE(a.empty());
    EXPECT_EQ(a.size(), 0);
    EXPECT_EQ(a.to_string(), "");
}

// ResizeOperationsTestSuite
TEST(ResizeOperationsTestSuite, EmptyPush)
{
    BitArray a;
    a.push_back(true);
    EXPECT_FALSE(a.empty());
    EXPECT_EQ(a.size(), 1);
    EXPECT_EQ(a.to_string(), "1");
}

TEST(ResizeOperationsTestSuite, ConsecutivePush)
{
    BitArray a;
    a.push_back(true);
    a.push_back(false);
    a.push_back(false);
    EXPECT_EQ(a.size(), 3);
    EXPECT_EQ(a.to_string(), "100");
}

TEST(ResizeOperationsTestSuite, EmptyClear)
{
    BitArray a;
    a.clear();
    EXPECT_TRUE(a.empty());
    EXPECT_EQ(a.size(), 0);
    EXPECT_EQ(a.to_string(), "");
}

TEST(ResizeOperationsTestSuite, NotEmptyClear)
{
    BitArray a(15);
    a.push_back(false);
    a.clear();
    EXPECT_TRUE(a.empty());
    EXPECT_EQ(a.size(), 0);
    EXPECT_EQ(a.to_string(), "");
}

TEST(ResizeOperationsTestSuite, BadResize)
{
    BitArray a(15);
    EXPECT_THROW(a.resize(-1), std::length_error);
}

TEST(ResizeOperationsTestSuite, ZeroResize)
{
    BitArray a(15);
    a.resize(0);

    EXPECT_TRUE(a.empty());
    EXPECT_EQ(a.size(), 0);
    EXPECT_EQ(a.to_string(), "");
}

TEST(ResizeOperationsTestSuite, EmptyResize)
{
    BitArray a;
    a.resize(5);
    EXPECT_FALSE(a.empty());
    EXPECT_EQ(a.size(), 5);
    EXPECT_EQ(a.to_string(), "00000");
}

TEST(ResizeOperationsTestSuite, ResizeSameSize)
{
    int length = 5;
    BitArray a;
    for (int i = 0; i < length; i++) {
        a.push_back(true);
    }
    a.resize(length);
    EXPECT_EQ(a.size(), length);
    EXPECT_EQ(a.to_string(), "11111");
}

TEST(ResizeOperationsTestSuite, ResizeLessSize)
{
    BitArray a;
    for (int i = 0; i < 4; i++) {
        a.push_back(true);
        a.push_back(false);
    }
    a.resize(3);
    EXPECT_EQ(a.size(), 3);
    EXPECT_EQ(a.to_string(), "101");
}

TEST(ResizeOperationsTestSuite, ResizeDefaultValue)
{
    BitArray a;
    for (int i = 0; i < 5; i++) {
        a.push_back(true);
    }
    a.resize(10);
    EXPECT_EQ(a.size(), 10);
    EXPECT_EQ(a.to_string(), "1111100000");
}

TEST(ResizeOperationsTestSuite, ResizeTrueValue)
{
    BitArray a;
    for (int i = 0; i < 5; i++) {
        a.push_back(false);
    }
    a.resize(10, true);
    EXPECT_EQ(a.size(), 10);
    EXPECT_EQ(a.to_string(), "0000011111");
}

// IndexOperationsTestSuite
TEST(IndexOperationsTestSuite, EmptyConstOperator)
{
    BitArray a;
    EXPECT_THROW(bool answer = a[0], std::out_of_range);
}

TEST(IndexOperationsTestSuite, NegativeConstOperator)
{
    BitArray a(15);
    EXPECT_THROW(bool answer = a[-1], std::out_of_range);
}

TEST(IndexOperationsTestSuite, OutOfBoundsConstOperator)
{
    BitArray a(15);
    EXPECT_THROW(bool answer = a[99999], std::out_of_range);
}

TEST(IndexOperationsTestSuite, ConstOperator)
{
    BitArray a;
    a.push_back(true);
    a.push_back(false);
    a.resize(4, true);
    EXPECT_TRUE(a[0]);
    EXPECT_FALSE(a[1]);
    EXPECT_TRUE(a[2]);
    EXPECT_TRUE(a[3]);
}

TEST(IndexOperationsTestSuite, EmptyAssignOperator)
{
    BitArray a;
    EXPECT_THROW(a[0] = false, std::out_of_range);
}

TEST(IndexOperationsTestSuite, NegativeAssignOperator)
{
    BitArray a(15);
    EXPECT_THROW(a[-1] = true, std::out_of_range);
}

TEST(IndexOperationsTestSuite, OutOfBoundsAssignOperator)
{
    BitArray a(15);
    EXPECT_THROW(a[99999] = true, std::out_of_range);
}

TEST(IndexOperationsTestSuite, AssignOperator)
{
    BitArray a(4);
    a[0] = true;
    a[1] = false;
    a[2] = true;
    a[3] = true;
    EXPECT_EQ(a.to_string(), "1011");
}

// SetResetOperationsTestSuite
TEST(SetResetOperationsTestSuite, SetEmpty)
{
    BitArray a;
    a.set();
    EXPECT_TRUE(a.empty());
}

TEST(SetResetOperationsTestSuite, Set)
{
    BitArray a(4);
    a[1] = 1;
    a.set();
    EXPECT_EQ(a.to_string(), "1111");
}

TEST(SetResetOperationsTestSuite, ResetEmpty)
{
    BitArray a;
    a.reset();
    EXPECT_TRUE(a.empty());
}

TEST(SetResetOperationsTestSuite, Reset)
{
    BitArray a;
    a.resize(4, true);
    a[1] = 0;
    a.reset();
    EXPECT_EQ(a.to_string(), "0000");
}

TEST(SetResetOperationsTestSuite, SetResetIndexEmpty)
{
    BitArray a;
    EXPECT_THROW(a.set(0), std::out_of_range);
    EXPECT_THROW(a.reset(0), std::out_of_range);
}

TEST(SetResetOperationsTestSuite, SetResetIndexNegative)
{
    BitArray a(15);
    EXPECT_THROW(a.set(-1), std::out_of_range);
    EXPECT_THROW(a.reset(-1), std::out_of_range);
}

TEST(SetResetOperationsTestSuite, SetResetIndexOutOfBounds)
{
    BitArray a(15);
    EXPECT_THROW(a.set(99999), std::out_of_range);
    EXPECT_THROW(a.reset(99999), std::out_of_range);
}

TEST(SetResetOperationsTestSuite, SetResetIndex)
{
    BitArray a(6);
    a[0] = true;
    a[1] = false;
    a[2] = true;
    a[3] = false;
    a[4] = true;
    a[5] = false;
    a.set(0);
    a.set(1);
    a.set(2, false);
    a.set(3, false);
    a.reset(4);
    a.reset(5);
    EXPECT_EQ(a.to_string(), "110000");
}

// AnyNoneCountTestSuite
TEST(AnyNoneCountTestSuite, EmptyBitArray)
{
    BitArray a;
    EXPECT_FALSE(a.any());
    EXPECT_TRUE(a.none());
    EXPECT_EQ(a.count(), 0);
}

TEST(AnyNoneCountTestSuite, FalseBitArray)
{
    BitArray a(6);
    EXPECT_FALSE(a.any());
    EXPECT_TRUE(a.none());
    EXPECT_EQ(a.count(), 0);
}

TEST(AnyNoneCountTestSuite, TrueBitArray)
{
    BitArray a(6);
    a.set();
    EXPECT_TRUE(a.any());
    EXPECT_FALSE(a.none());
    EXPECT_EQ(a.count(), 6);
}

TEST(AnyNoneCountTestSuite, NormalBitArray)
{
    BitArray a(6);
    a[1] = true;
    a[4] = true;
    EXPECT_TRUE(a.any());
    EXPECT_FALSE(a.none());
    EXPECT_EQ(a.count(), 2);
}

// SelfBitwiseOperationsTestSuite
TEST(SelfBitwiseOperationsTestSuite, EmptyBitArrays)
{
    BitArray a, b;
    a &= b;
    EXPECT_TRUE(a.empty());

    BitArray a, b;
    a |= b;
    EXPECT_TRUE(a.empty());

    BitArray a, b;
    a ^= b;
    EXPECT_TRUE(a.empty());
}

TEST(SelfBitwiseOperationsTestSuite, NotEqualSizeBitArrays)
{
    BitArray a(5), b(8);
    EXPECT_THROW(a &= b, std::length_error);

    BitArray a(5), b(8);
    EXPECT_THROW(a |= b, std::length_error);

    BitArray a(5), b(8);
    EXPECT_THROW(a ^= b, std::length_error);
}

TEST(SelfBitwiseOperationsTestSuite, NormalBitArrays)
{
    BitArray sample_a(4), sample_b(4);
    sample_a[1] = true;
    sample_a[3] = true; // "0101"
    sample_b[2] = true;
    sample_b[3] = true; // "0011"

    BitArray a(sample_a), b(sample_b);
    a &= b;
    EXPECT_EQ(a.to_string(), "0001");

    BitArray a(sample_a), b(sample_b);
    a |= b;
    EXPECT_EQ(a.to_string(), "0111");

    BitArray a(sample_a), b(sample_b);
    a ^= b;
    EXPECT_EQ(a.to_string(), "0110");
}

// BitwiseOperationsTestSuite
TEST(BitwiseOperationsTestSuite, EmptyBitArrays)
{
    BitArray a, b;
    BitArray c = a & b;
    EXPECT_TRUE(c.empty());

    BitArray a, b;
    BitArray c = a | b;
    EXPECT_TRUE(c.empty());

    BitArray a, b;
    BitArray c = a ^ b;
    EXPECT_TRUE(c.empty());

    BitArray a;
    BitArray c = ~a;
    EXPECT_TRUE(c.empty());
}

TEST(BitwiseOperationsTestSuite, NotEqualSizeBitArrays)
{
    BitArray a(5), b(8);
    EXPECT_THROW(BitArray c = a & b, std::length_error);

    BitArray a(5), b(8);
    EXPECT_THROW(BitArray c = a | b, std::length_error);

    BitArray a(5), b(8);
    EXPECT_THROW(BitArray c = a ^ b, std::length_error);
}

TEST(BitwiseOperationsTestSuite, NormalBitArrays)
{
    BitArray sample_a(4), sample_b(4);
    sample_a[1] = true;
    sample_a[3] = true; // "0101"
    sample_b[2] = true;
    sample_b[3] = true; // "0011"

    BitArray a(sample_a), b(sample_b);
    BitArray c = a & b;
    EXPECT_EQ(c.to_string(), "0001");

    BitArray a(sample_a), b(sample_b);
    BitArray c = a | b;
    EXPECT_EQ(c.to_string(), "0111");

    BitArray a(sample_a), b(sample_b);
    BitArray c = a ^ b;
    EXPECT_EQ(c.to_string(), "0110");

    BitArray c = ~sample_a;
    EXPECT_EQ(c.to_string(), "1010");
}

// CompareTestSuite
TEST(CompareTestSuite, EmptyBitArrays)
{
    BitArray a, b;
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST(CompareTestSuite, NotEqualSizeBitArrays)
{
    BitArray a(5), b(8);
    EXPECT_THROW(a == b, std::length_error);
    EXPECT_THROW(a != b, std::length_error);
}

TEST(CompareTestSuite, EqualBitArrays)
{
    BitArray sample(12, 29039);
    BitArray a(sample), b(sample);

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST(CompareTestSuite, NotEqualBitArrays)
{
    BitArray sample(5);
    BitArray a(sample), b(sample);
    a[4] = true;

    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

// BitShiftsTestSuite
TEST(BitShiftsTestSuite, EmptyBitShift)
{
    BitArray a_r;
    a_r >>= 5;
    EXPECT_TRUE(a_r.empty());

    BitArray a_l;
    a_l <<= 5;
    EXPECT_TRUE(a_l.empty());

    BitArray a_r;
    BitArray b_r = a_r >> 5;
    EXPECT_TRUE(a_r.empty());

    BitArray a_l;
    BitArray b_l = a_l << 5;
    EXPECT_TRUE(a_l.empty());

}

TEST(BitShiftsTestSuite, NegativeBitShift)
{
    BitArray a_r(5);
    EXPECT_THROW(a_r >>= -1, std::length_error);

    BitArray a_l(5);
    EXPECT_THROW(a_l <<= -1, std::length_error);

    BitArray a_r(5);
    EXPECT_THROW(BitArray b_r = a_r >> -1, std::length_error);

    BitArray a_l(5);
    EXPECT_THROW(BitArray b_l = a_l << -1, std::length_error);
}

TEST(BitShiftsTestSuite, VeryBigBitShift)
{
    BitArray a_r(6);
    a_r.set();
    a_r >>= 999999;
    EXPECT_EQ(a_r.to_string(), "000000");

    BitArray a_l(6);
    a_l.set();
    a_l >>= 999999;
    EXPECT_EQ(a_l.to_string(), "000000");

    BitArray a_r(6);
    a_r.set();
    BitArray b_r = a_r >> 999999;
    EXPECT_EQ(b_r.to_string(), "000000");

    BitArray a_l(6);
    a_l.set();
    BitArray b_l = a_l >> 999999;
    EXPECT_EQ(b_l.to_string(), "000000");
}

TEST(BitShiftsTestSuite, NormalBitShift)
{
    BitArray sample(6);
    sample[0] = true;
    sample[2] = true;
    sample[4] = true;

    BitArray a_r(sample);
    a_r >>= 2;
    EXPECT_EQ(a_r.to_string(), "001010");

    BitArray a_l(sample);
    a_l >>= 2;
    EXPECT_EQ(a_l.to_string(), "101000");

    BitArray b_r = sample >> 2;
    EXPECT_EQ(b_r.to_string(), "001010");

    BitArray b_l = sample >> 2;
    EXPECT_EQ(b_l.to_string(), "101000");
}