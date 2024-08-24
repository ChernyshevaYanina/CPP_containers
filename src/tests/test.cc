
#include <array>
#include <iterator>
#include <list>
#include <vector>

#include "../containers.h"
#include "../containersplas.h"
#include "main.h"

using namespace my_сontainers;
using std::cout;

TEST(myVector, shrink) {
  myVector<std::string> vec1;
  vec1.push_back("aaa");
  vec1.push_back("bbb");
  vec1.push_back("ccc");

  std::vector<std::string> vec2;
  vec2.push_back("aaa");
  vec2.push_back("bbb");
  vec2.push_back("ccc");

  ASSERT_EQ(vec1.capacity(), vec2.capacity());

  vec1.shrink_to_fit();
  vec2.shrink_to_fit();

  ASSERT_EQ(vec1.capacity(), vec2.capacity());
}

TEST(myVector, constr_copy) {
  myVector<int> vec1;
  vec1.push_back(1);
  vec1.push_back(2);
  vec1.push_back(3);

  myVector<int> vec2(vec1);

  ASSERT_EQ(vec2[0], 1);
  ASSERT_EQ(vec2[1], 2);
  ASSERT_EQ(vec2[2], 3);
  ASSERT_EQ(vec1.capacity(), vec2.capacity());
  ASSERT_EQ(vec1.size(), vec2.size());
}

TEST(myVector, init_list) {
  myVector<int> vec{1, 2, 3};

  ASSERT_EQ(vec[0], 1);
  ASSERT_EQ(vec[1], 2);
  ASSERT_EQ(vec[2], 3);
}

TEST(myVector, iterator_1) {
  myVector<int> vec;
  vec.push_back(1);
  vec.push_back(2);

  auto iter = vec.begin();
  ASSERT_EQ(vec[0], *iter);
  ASSERT_EQ(vec[1], *(++iter));
  int* d = vec.data();
  ASSERT_EQ(*(d + 1), *iter);
}

TEST(myVector, empty_true) {
  myVector<int> vec;
  ASSERT_TRUE(vec.empty());
}

TEST(myVector, empty_false) {
  myVector<int> vec;
  vec.push_back(123);
  ASSERT_FALSE(vec.empty());
}

TEST(myVector, resize_capacity) {
  myVector<int> vec1(0);
  vec1.reserve(5);
  ASSERT_EQ(vec1.capacity(), 5);
  vec1.push_back(123);
  vec1.push_back(456);
  vec1.push_back(789);

  vec1.resize(20);
  ASSERT_EQ(vec1.size(), 20);

  vec1.pop_back();
  ASSERT_EQ(vec1.size(), 19);
}

TEST(myVector, at_1) {
  myVector<std::string> vec1;
  vec1.push_back("aaaa");

  ASSERT_EQ(vec1[0], "aaaa");
  EXPECT_ANY_THROW({ vec1.at(2); });
}

TEST(myVector, at_2) {
  myVector<int> vec1(3);
  vec1.push_back(1);
  vec1.push_back(2);

  std::vector<int> vec2(3);
  vec2.push_back(1);
  vec2.push_back(2);

  ASSERT_EQ(vec1.at(3), vec2.at(3));
}

TEST(myVector, clear) {
  myVector<double> vec;
  vec.push_back(123.123);
  vec.push_back(12.22);

  vec.clear();
  ASSERT_EQ(vec.size(), 0);
}

TEST(myVector, swap) {
  myVector<int> vec1{1, 2, 3};
  myVector<int> vec2{4, 3, 2, 1};

  vec1.swap(vec2);

  ASSERT_EQ(vec1[0], 4);
  ASSERT_EQ(vec1[1], 3);
  ASSERT_EQ(vec1[2], 2);
  ASSERT_EQ(vec1[3], 1);
  ASSERT_EQ(vec1.size(), 4);
}

TEST(myVector, erase) {
  myVector<int> vec1;
  vec1.push_back(1);
  vec1.push_back(2);
  vec1.push_back(3);
  vec1.push_back(4);

  std::vector<int> vec2;
  vec2.push_back(1);
  vec2.push_back(2);
  vec2.push_back(3);
  vec2.push_back(4);

  vec1.erase(vec1.begin() + 2);
  vec2.erase(vec2.begin() + 2);

  auto it1 = vec1.begin();
  auto it2 = vec2.begin();
  for (; it1 != vec1.end() && it2 != vec2.end(); ++it1, ++it2) {
    ASSERT_EQ(*it1, *it2);
  }
}

TEST(myVector, insert_1) {
  myVector<int> vec1;
  vec1.push_back(1);
  vec1.push_back(2);
  vec1.push_back(3);
  vec1.push_back(4);
  vec1.push_back(5);

  std::vector<int> vec2;
  vec2.push_back(1);
  vec2.push_back(2);
  vec2.push_back(3);
  vec2.push_back(4);
  vec2.push_back(5);

  vec1.insert(vec1.begin(), 100);
  vec1.insert(vec1.end(), 200);
  vec1.insert(vec1.begin() + vec1.size() / 2, 300);

  vec2.insert(vec2.begin(), 100);
  vec2.insert(vec2.end(), 200);
  vec2.insert(vec2.begin() + vec2.size() / 2, 300);

  auto it1 = vec1.begin();
  auto it2 = vec2.begin();
  for (; it1 != vec1.end() && it2 != vec2.end(); ++it1, ++it2)
    ASSERT_EQ(*it1, *it2);
}

TEST(myVector, insert_2) {
  myVector<double> vec1{1.1, 2.2, 3.3, 4.4, 5.5};

  std::vector<double> vec2{1.1, 2.2, 3.3, 4.4, 5.5};
  vec1.insert(vec1.begin(), 10.10);
  vec2.insert(vec2.begin(), 10.10);
  auto it1 = vec1.begin();
  auto it2 = vec2.begin();
  for (; it1 != vec1.end() && it2 != vec2.end(); ++it1, ++it2)
    ASSERT_EQ(*it1, *it2);
}

TEST(myVector, insert_many) {
  myVector<int> vec{1, 2, 6};
  vec.insert_many(vec.cbegin() + 2, 3, 4, 5);
  double num = 1;
  for (auto it = vec.begin(); it != vec.end(); ++it) {
    ASSERT_EQ(*it, num);
    num += 1;
  }
}
TEST(myVector, insert_many_back) {
  myVector<int> vec{1, 2, 3};
  vec.insert_many_back(4, 5, 6);
  double num = 1;
  for (auto it = vec.begin(); it != vec.end(); ++it) {
    ASSERT_EQ(*it, num);
    num += 1;
  }
}

TEST(myArray, constructor) {
  myArray<int, 4> arr1{5, 3, 5, 5};
  myArray<int, 4> arr2(arr1);

  auto it1 = arr1.begin();
  auto it2 = arr2.begin();
  for (; it1 != arr1.end() && it2 != arr2.end(); ++it1, ++it2) {
    ASSERT_EQ(*it1, *it2);
  }
}

TEST(myArray, constructor_2) {
  myArray<int, 4> arr1{5, 3, 5, 5};
  myArray<int, 4> arr2(std::move(arr1));
  ASSERT_EQ(arr2.front(), 5);
  ASSERT_EQ(arr2.at(1), 3);
  ASSERT_EQ(arr2.at(2), 5);
  ASSERT_EQ(arr2.at(3), 5);
  ASSERT_EQ(arr1.at(0), 0);
}

TEST(myArray, op_eq) {
  myArray<int, 4> arr1{5, 3, 5, 3};
  myArray<int, 4> arr2;

  arr2 = arr1;
  ASSERT_EQ(arr2[0], 5);
  ASSERT_EQ(arr2[1], 3);
  ASSERT_EQ(arr2[2], 5);
  ASSERT_EQ(arr2[3], 3);
}

TEST(myArray, iter) {
  myArray<int, 4> a1{1, 2, 3, 4};
  auto i = a1.begin();
  ASSERT_EQ(*i, 1);
  ++i;
  ASSERT_EQ(*i, 2);
  --i;
  ASSERT_EQ(*i, 1);

  auto j = a1.end();
  --j;
  ASSERT_EQ(*j, 4);
}

TEST(myArray, empty) {
  myArray<int, 0> a;
  ASSERT_EQ(a.empty(), true);
}

TEST(myArray, size) {
  myArray<int, 1> a;
  ASSERT_EQ(a.size(), 1);
}

TEST(myArray, max) {
  myArray<int, 11> a1;
  std::array<int, 11> a2;
  ASSERT_EQ(a1.max_size(), a2.max_size());
}

TEST(myArray, swap) {
  myArray<int, 3> arr1{1, 2, 3};
  myArray<int, 3> arr2{6, 5, 4};

  arr1.swap(arr2);
  int num = 6;
  for (auto it = arr1.begin(); it != arr1.end(); ++it) {
    ASSERT_EQ(*it, num);
    --num;
  }

  num = 1;
  for (auto it = arr2.begin(); it != arr2.end(); ++it) {
    ASSERT_EQ(*it, num);
    ++num;
  }
}

TEST(myArray, fill) {
  myArray<int, 10> arr;

  arr.fill(666);

  for (auto it = arr.begin(); it != arr.end(); ++it) ASSERT_EQ(*it, 666);
}

TEST(myArray, front_back) {
  myArray<int, 3> arr1{1, 2, 3};
  std::array<int, 3> arr2{1, 2, 3};

  ASSERT_EQ(arr1.front(), arr2.front());
  ASSERT_EQ(arr1.back(), arr2.back());
}

TEST(myArray, front_error) {
  myArray<char, 0> arr;
  ASSERT_ANY_THROW(arr.front());
}

TEST(myArray, back_error) {
  myArray<double, 0> arr;
  ASSERT_ANY_THROW(arr.back());
}

TEST(myArray, data) {
  myArray<int, 4> arr1{1, 2, 3, 4};
  std::array<int, 4> arr2{1, 2, 3, 4};

  auto data1 = arr1.data();
  auto data2 = arr2.data();

  ASSERT_EQ(data1[0], data2[0]);
  ASSERT_EQ(data1[1], data2[1]);
  ASSERT_EQ(data1[2], data2[2]);
  ASSERT_EQ(data1[3], data2[3]);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
