#include "gtest/gtest.h"
#include "../src/production_center.h"

namespace {

TEST(ProductionCenter, Starts_with_0_bouquets) {
  ProductionCenter center;

  EXPECT_EQ(0, center.stock_bouquet);
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
