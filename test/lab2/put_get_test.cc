#include "data/csv_data_loader.h"
#include "table/column_table.h"
#include "table/indexed_row_table.h"
#include "table/row_table.h"
#include "test_base.h"
#include <gtest/gtest.h>
#include <iostream>

using namespace bytedance_db_project;

class PutGetTest : public TestBase {};

TEST_F(PutGetTest, RowTableTest) {
  RowTable rt;
  rt.Load(loader);
  auto row_id = 4;
  auto col_id = 0;
  ASSERT_EQ(8, rt.GetIntField(row_id, col_id));
  rt.PutIntField(row_id, col_id, 10);
  ASSERT_EQ(10, rt.GetIntField(row_id, col_id));
}

TEST_F(PutGetTest, ColumnTableTest) {
  ColumnTable ct;
  ct.Load(loader);
  auto row_id = 4;
  auto col_id = 0;
  ASSERT_EQ(8, ct.GetIntField(row_id, col_id));
  ct.PutIntField(row_id, col_id, 10);
  ASSERT_EQ(10, ct.GetIntField(row_id, col_id));
}

TEST_F(PutGetTest, IndexedRowTableTest) {
  IndexedRowTable it(0);
  it.Load(loader);
  auto row_id = 4;
  auto col_id = 0;
  ASSERT_EQ(8, it.GetIntField(row_id, col_id));
  it.PutIntField(row_id, col_id, 10);
  ASSERT_EQ(10, it.GetIntField(row_id, col_id));
}
