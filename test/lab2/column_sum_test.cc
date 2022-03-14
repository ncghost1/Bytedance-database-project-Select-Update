#include "data/csv_data_loader.h"
#include "table/column_table.h"
#include "table/custom_table.h"
#include "table/indexed_row_table.h"
#include "table/row_table.h"
#include "table/table.h"
#include "test_base.h"
#include <gtest/gtest.h>
#include <iostream>

using namespace bytedance_db_project;

class ColumnSumTest : public TestBase {};

TEST_F(ColumnSumTest, TestRowTable) {
  RowTable rt;
  rt.Load(loader);
  ASSERT_EQ(68, rt.ColumnSum());
}

TEST_F(ColumnSumTest, TestColumnTable) {
  ColumnTable rt;
  rt.Load(loader);
  ASSERT_EQ(68, rt.ColumnSum());
}

TEST_F(ColumnSumTest, TestIndexedTable) {
  IndexedRowTable rt(0);
  rt.Load(loader);
  ASSERT_EQ(68, rt.ColumnSum());
}