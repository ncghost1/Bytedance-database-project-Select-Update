#include "data/csv_data_loader.h"
#include "table/column_table.h"
#include "table/indexed_row_table.h"
#include "table/row_table.h"
#include "test_base.h"
#include <gtest/gtest.h>
#include <iostream>

using namespace bytedance_db_project;

class PredicatedColumnSumTest : public TestBase {};

TEST_F(PredicatedColumnSumTest, RowTableTest) {
  RowTable rt;
  rt.Load(loader);
  ASSERT_EQ(49, rt.PredicatedColumnSum(3, 5));
}

TEST_F(PredicatedColumnSumTest, ColumnTableTest) {
  ColumnTable ct;
  ct.Load(loader);
  ASSERT_EQ(49, ct.PredicatedColumnSum(3, 5));
}

TEST_F(PredicatedColumnSumTest, IndexedRowTableTest) {
  IndexedRowTable it(0);
  it.Load(loader);
  ASSERT_EQ(49, it.PredicatedColumnSum(3, 5));
}
