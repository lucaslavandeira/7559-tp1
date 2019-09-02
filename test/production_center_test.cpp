#include "gtest/gtest.h"
#include "../src/production_center.h"

class ProductionCenterTest : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if its body
  // is empty.

  ProductionCenterTest() {
     // You can do set-up work for each test here.
  }

  ~ProductionCenterTest() override {
     // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  void SetUp() override {
     // Code here will be called immediately after the constructor (right
     // before each test).
  }

  void TearDown() override {
     // Code here will be called immediately after each test (right
     // before the destructor).
  }

  // Objects declared here can be used by all tests in the test suite for ProductionCenter.
  ProductionCenter center;
};

TEST_F(ProductionCenterTest, production_initial_stock_should_be_zero) {
  EXPECT_EQ(0, center.stock_bouquet);
}

TEST_F(ProductionCenterTest, harvesting_returns_40_bouquets) {
  EXPECT_EQ(40, center.harvest());
}
