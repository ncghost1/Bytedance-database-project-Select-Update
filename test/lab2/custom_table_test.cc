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

class CustomTest : public TestBase {};

TEST_F(CustomTest, TestRowTable) {
  CustomTable ct;
  ct.Load(loader);
  ASSERT_EQ(68, ct.ColumnSum());
  ASSERT_EQ(166, ct.PredicatedAllColumnsSum(3));
  ASSERT_EQ(342, ct.PredicatedAllColumnsSum(-1));
  ASSERT_EQ(49, ct.PredicatedColumnSum(3, 5));
  ASSERT_EQ(9, ct.PredicatedUpdate(3));
  ASSERT_EQ(360, ct.PredicatedAllColumnsSum(-1));
}