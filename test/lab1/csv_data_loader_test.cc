#include "data/csv_data_loader.h"
#include "test_base.h"
#include <gtest/gtest.h>
#include <iostream>

class CsvDataLoaderTest : public TestBase {};

TEST_F(CsvDataLoaderTest, BasicTest) {
  std::vector<char *> rows = loader->GetRows();
  char *row_0 = rows.at(0);
  int32_t expected_result[5] = {0, 2, 2, 3, 4};
  for (auto i = 0; i < 5; i++) {
    ASSERT_EQ(*(int32_t *)(row_0 + sizeof(int32_t) * i), expected_result[i]);
  }
}
