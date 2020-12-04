// Copyright 2020 Your Name <your_email>

#include <gtest/gtest.h>

#include <string>

#include "shared_ptr.hpp"

TEST(SharedPtr, EmptyConstructor) {
  SharedPtr<int> shared_ptr;
  ASSERT_EQ(shared_ptr.get(), nullptr);
  ASSERT_EQ(shared_ptr.get_counter(), nullptr);
}
TEST(SharedPtr, Constructor) {
  SharedPtr<int> shared_ptr1(new int{100});

  ASSERT_EQ(*shared_ptr1.get(), 100);
  ASSERT_EQ(shared_ptr1.use_count(), 1);

  SharedPtr<int> shared_ptr2(new int{1000});

  ASSERT_EQ(*shared_ptr2.get(), 1000);
  ASSERT_EQ(shared_ptr2.use_count(), 1);
}

TEST(SharedPtr, Copy_Constructor) {
  const SharedPtr shared_ptr1(new double{3.141956});
  SharedPtr shared_ptr2(new double{2.718281828});
  SharedPtr shared_ptr3(new std::string{"KAK VSE DOSTALO!"});

  shared_ptr2 = shared_ptr1;
  SharedPtr shared_ptr4(shared_ptr3);

  ASSERT_EQ(*shared_ptr1, *shared_ptr2);
  ASSERT_EQ(*shared_ptr3, *shared_ptr4);
  ASSERT_EQ(shared_ptr1.use_count(), shared_ptr2.use_count());
  ASSERT_EQ(shared_ptr3.use_count(), shared_ptr4.use_count());
}

TEST(SharedPtr, Move_Constructor) {
  SharedPtr shared_ptr1(new double{3.141956});
  SharedPtr shared_ptr2(new double{2.718281828});
  SharedPtr shared_ptr3(new std::string{"MOVE, PLEASE!!!"});

  ASSERT_EQ(shared_ptr1.use_count(), 1);
  ASSERT_EQ(shared_ptr2.use_count(), 1);
  ASSERT_EQ(shared_ptr3.use_count(), 1);

  ASSERT_EQ(*shared_ptr1, 3.141956);
  ASSERT_EQ(*shared_ptr3, "MOVE, PLEASE!!!");

  shared_ptr2 = std::move(shared_ptr1);
  SharedPtr shared_ptr4(std::move(shared_ptr3));

  ASSERT_EQ(*shared_ptr2, 3.141956);
  ASSERT_EQ(*shared_ptr4, "MOVE, PLEASE!!!");

  ASSERT_EQ(shared_ptr1.get(), nullptr);
  ASSERT_EQ(shared_ptr1.get_counter(), nullptr);
  ASSERT_EQ(shared_ptr3.get(), nullptr);
  ASSERT_EQ(shared_ptr3.get_counter(), nullptr);
}

class Car {
 private:
  int speed;

 public:
  explicit Car(int SPEED) : speed(SPEED) {}
  [[nodiscard]] int Get_Speed() const { return speed; }
};

TEST(SharedPtr, Test_Getter) {
  SharedPtr<Car> shared_ptr(new Car{999999999});

  ASSERT_EQ(shared_ptr->Get_Speed(), 999999999);
}

TEST(SharedPtr, Test_Reset) {
  SharedPtr shared_ptr1(new double{3.141956});
  SharedPtr shared_ptr2(new double{2.718281828});
  SharedPtr shared_ptr3(static_cast<const SharedPtr<double>>(shared_ptr2));

  shared_ptr1.reset();
  ASSERT_EQ(shared_ptr1.get(), nullptr);
  ASSERT_EQ(shared_ptr1.get_counter(), nullptr);

  shared_ptr2.reset(new double{555});
  ASSERT_EQ(*shared_ptr2, 555);
  ASSERT_EQ(shared_ptr2.use_count(), 1);
  ASSERT_EQ(*shared_ptr3, 2.718281828);
  ASSERT_EQ(shared_ptr3.use_count(), 1);
}

TEST(SharedPtr, Swap1) {
  SharedPtr shared_ptr1{new int{100}};
  SharedPtr shared_ptr2{new int{1000}};

  shared_ptr1.swap(shared_ptr2);

  ASSERT_EQ(*(shared_ptr1.get()), 1000);
  ASSERT_EQ(shared_ptr1.operator bool(), true);
  ASSERT_EQ(shared_ptr1.use_count(), 1);

  ASSERT_EQ(*(shared_ptr2.get()), 100);
  ASSERT_EQ(shared_ptr2.operator bool(), true);
  ASSERT_EQ(shared_ptr2.use_count(), 1);
}

TEST(SharedPtr, Swap2) {
  SharedPtr shared_ptr1{new int{100}};
  SharedPtr shared_ptr2{new int{1000}};
  SharedPtr shared_ptr3 = shared_ptr2;

  shared_ptr1.swap(shared_ptr2);

  ASSERT_EQ(shared_ptr1.use_count(), 2);
  ASSERT_EQ(shared_ptr2.use_count(), 1);
  ASSERT_EQ(shared_ptr3.use_count(), 2);
}
TEST(SharedPtr, Get) {
  SharedPtr shared_ptr1{new int{100}};
  *shared_ptr1 = 1000;

  ASSERT_EQ(*shared_ptr1, 1000);
  ASSERT_EQ(shared_ptr1.use_count(), 1);
}

TEST(SharedPtr, Bool_Operator) {
  SharedPtr<int> shared_ptr1{};
  SharedPtr shared_ptr2(new int{23235});

  ASSERT_EQ(shared_ptr1.operator bool(), false);
  ASSERT_EQ(shared_ptr2.operator bool(), true);
}

template <class T>
auto IsCopyAssignment(T& reference1, T& reference2) -> T& {
  reference1 = reference2;
  return reference1;
}
TEST(SharedPtr, ThisCopyAssigment) {
  SharedPtr shared_ptr1{new int{45345435}};

  EXPECT_EQ(*IsCopyAssignment(shared_ptr1, shared_ptr1), 45345435);
  EXPECT_EQ(IsCopyAssignment<SharedPtr<int>>(shared_ptr1, shared_ptr1).use_count(), 1);
}
template <class T>
auto IsMoveAssignment(T& reference1, T& reference2) -> T& {
  reference1 = std::move(reference2);
  return reference1;
}
TEST(SharedPtr, IsMoveAssignment) {
  SharedPtr shared_ptr1{new int{45345435}};

  EXPECT_EQ(*IsMoveAssignment(shared_ptr1, shared_ptr1), 45345435);
  EXPECT_EQ(IsMoveAssignment(shared_ptr1, shared_ptr1).use_count(), 1);
}
