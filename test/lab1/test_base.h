#pragma once

#include "data/csv_data_loader.h"
#include <gtest/gtest.h>

using namespace bytedance_db_project;
static const std::string kTestCsvFilePath = "./test.csv";
static const int32_t kNumCols = 5;

class TestBase : public ::testing::Test {
protected:
  void SetUp() override {
    loader = new CsvDataLoader(kTestCsvFilePath, kNumCols);
  }

  void TearDown() override {
    if (loader) {
      delete loader;
      loader = nullptr;
    }
  }
  CsvDataLoader *loader;
};
