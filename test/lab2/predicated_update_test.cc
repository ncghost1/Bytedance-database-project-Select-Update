#include "data/csv_data_loader.h"
#include "table/column_table.h"
#include "table/indexed_row_table.h"
#include "table/row_table.h"
#include "test_base.h"
#include <gtest/gtest.h>
#include <iostream>

using namespace bytedance_db_project;

class PredicatedUpdateTest : public TestBase {};

TEST_F(PredicatedUpdateTest, RowTableTest) {
  RowTable rt;
  rt.Load(loader);
  ASSERT_EQ(9, rt.PredicatedUpdate(3));
}

TEST_F(PredicatedUpdateTest, ColumnTableTest) {
  ColumnTable ct;
  ct.Load(loader);
  ASSERT_EQ(9, ct.PredicatedUpdate(3));
}

TEST_F(PredicatedUpdateTest, IndexedRowTableTest) {
  IndexedRowTable it(0);
  it.Load(loader);
  ASSERT_EQ(9, it.PredicatedUpdate(3));
}
