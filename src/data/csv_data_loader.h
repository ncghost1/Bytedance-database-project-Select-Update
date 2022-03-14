/*****************************************************************************
 * Copyright (c) 2022, Bytedance Inc. All rights reserved.
 *
 * @file: csv_data_loader.h
 *
 * @description: Define the CSV data loader.
 *
 * @created_at: 2021/12
 *
 * Managed by database team @ByteDance.
 *****************************************************************************/
#pragma once
#include "base_data_loader.h"
#include <mutex>
#include <string>

namespace bytedance_db_project {

class CsvDataLoader : public BaseDataLoader {
public:
  CsvDataLoader(std::string file_path, int32_t num_cols);

  ~CsvDataLoader() override;

  int32_t GetNumCols() override;

  std::vector<char *> GetRows() override;

private:
  std::string file_path_{""};
  int32_t num_cols_{0};
  std::vector<char *> *rows_{nullptr};
  std::mutex mtx_;
};

} // namespace bytedance_db_project
