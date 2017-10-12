#include <iostream>
#include <gtest/gtest.h>
#include "Buff.h"

//#pragma comment (lib, "gtestd.lib")

//My first unit test ever
TEST(BufferTests, AssignmentOperator) {
	CircularBuffer a(10, 'w');
	CircularBuffer b(25);
	b = a;
	EXPECT_EQ(a, b);
}

//Checking Capacity&Value Constructor
TEST(BufferTests, CapacityValueConstructor) {
	CircularBuffer a(5, 'w');
	for (int i = 0; i < 5; ++i) {
		EXPECT_EQ(a[i], 'w');
	}
	EXPECT_TRUE(a.full());
	EXPECT_FALSE(a.empty());
	EXPECT_EQ(a.reserve(), 0);
	EXPECT_EQ(a.size(), 5);
	EXPECT_EQ(a.capacity(), 5);
}

TEST(BufferTests, CopyConstructor) {
  CircularBuffer a(10, 'a');
  CircularBuffer b = a;
  EXPECT_EQ(a, b);
}

TEST(BufferTests, push_back) {
  CircularBuffer a(3);
  EXPECT_FALSE(a.full());
  EXPECT_TRUE(a.empty());
  EXPECT_EQ(a.reserve(), 3);

  a.push_back('a');
  a.push_back('b');
  a.push_back('c');

  EXPECT_EQ(a.size(), 3);
  EXPECT_FALSE(a.empty());
  EXPECT_TRUE(a.full());

  EXPECT_EQ(a[0], 'a');
  EXPECT_EQ(a[1], 'b');
  EXPECT_EQ(a[2], 'c');
}

TEST(BufferTests, push_front) {
  CircularBuffer a(3);
  EXPECT_FALSE(a.full());
  EXPECT_TRUE(a.empty());
  EXPECT_EQ(a.reserve(), 3);

  a.push_front('a');
  a.push_front('b');
  a.push_front('c');

  EXPECT_EQ(a.size(), 3);
  EXPECT_FALSE(a.empty());
  EXPECT_TRUE(a.full());

  EXPECT_EQ(a[0], 'c');
  EXPECT_EQ(a[1], 'b');
  EXPECT_EQ(a[2], 'a');
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}