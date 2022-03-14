/*****************************************************************************
 * Copyright (c) 2022, Bytedance Inc. All rights reserved.
 *
 * @file: base_data_loader.h
 *
 * @description: Define the basic data loader interface.
 *
 * @created_at: 2021/12
 *
 * Managed by database team @ByteDance.
 *****************************************************************************/
#pragma once
#include "univ.h"
#include <vector>

namespace bytedance_db_project {

class BaseDataLoader {
public:
  BaseDataLoader() = default;

  virtual ~BaseDataLoader() = default;

  virtual int32_t GetNumCols() = 0;

  virtual std::vector<char *> GetRows() = 0;
};

} // namespace bytedance_db_project
