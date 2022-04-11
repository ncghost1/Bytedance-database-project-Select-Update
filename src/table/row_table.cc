#include "row_table.h"
#include <cstring>

namespace bytedance_db_project {
RowTable::RowTable() {}

RowTable::~RowTable() {
  if (rows_ != nullptr) {
    delete rows_;
    rows_ = nullptr;
  }
}

void RowTable::Load(BaseDataLoader *loader) {
  num_cols_ = loader->GetNumCols();
  auto rows = loader->GetRows();
  num_rows_ = rows.size();
  rows_ = new char[FIXED_FIELD_LEN * num_rows_ * num_cols_];
  for (auto row_id = 0; row_id < num_rows_; row_id++) {
    auto &cur_row = rows.at(row_id);
    std::memcpy(rows_ + row_id * (FIXED_FIELD_LEN * num_cols_), cur_row,
                FIXED_FIELD_LEN * num_cols_);
  }
}
 
int32_t RowTable::GetIntField(int32_t row_id, int32_t col_id) {
    // TODO: Implement this!
    //首先计算偏移量
    auto offset = FIXED_FIELD_LEN * row_id * num_cols_ + FIXED_FIELD_LEN * col_id;

    //判断偏移量是否在合法范围内
    if (offset >= 0 && offset < FIXED_FIELD_LEN * num_rows_ * num_cols_) {

        //通过偏移量获取对应int32_t类型数据并返回
        return *(int32_t*)(rows_ + offset);
    }

    return 0;
}

void RowTable::PutIntField(int32_t row_id, int32_t col_id, int32_t field) {
    // TODO: Implement this!
    //首先计算偏移量
    auto offset = FIXED_FIELD_LEN * row_id * num_cols_ + FIXED_FIELD_LEN * col_id;

    //判断偏移量是否在合法范围内
    if (offset >= 0 && offset < FIXED_FIELD_LEN * num_rows_ * num_cols_) {

        //通过偏移量获取对应int32_t类型的数据并赋值为field
        *(int32_t*)(rows_ + offset) = field;
    }

}

int64_t RowTable::ColumnSum() {
    // TODO: Implement this!

    int64_t sum = 0;

    for (auto row_id = 0; row_id < num_rows_; row_id++) {

        //col0所在地址的偏移量
        auto offset = FIXED_FIELD_LEN * row_id * num_cols_;
        sum += *(int32_t*)(rows_ + offset);
    }

    return sum;
}

int64_t RowTable::PredicatedColumnSum(int32_t threshold1, int32_t threshold2) {
    // TODO: Implement this!
    int64_t sum = 0;
    int32_t col_0 = 0;
    if(num_cols_>=3) {
        for (auto row_id = 0; row_id < num_rows_; row_id++) {
            //分别取col0,col1,col2的偏移量
            auto offset_c0 = FIXED_FIELD_LEN * row_id * num_cols_ + FIXED_FIELD_LEN * col_0;
            auto offset_c1 = FIXED_FIELD_LEN * row_id * num_cols_ + FIXED_FIELD_LEN * (col_0 + 1);
            auto offset_c2 = FIXED_FIELD_LEN * row_id * num_cols_ + FIXED_FIELD_LEN * (col_0 + 2);

            //分别取出col0,col1,col2的值
            int32_t val_c0 = *(int32_t*)(rows_ + offset_c0);
            int32_t val_c1 = *(int32_t*)(rows_ + offset_c1);
            int32_t val_c2 = *(int32_t*)(rows_ + offset_c2);

            //满足条件加入sum
            if (val_c1 > threshold1 && val_c2 < threshold2) {
                sum += val_c0;
            }
        }
    }
    return sum;
}

int64_t RowTable::PredicatedAllColumnsSum(int32_t threshold) {
  // TODO: Implement this!
    int64_t sum = 0;
    for (auto row_id = 0; row_id < num_rows_; row_id++) {
        for (auto col_id = 0; col_id < num_cols_; col_id++) {
            auto offset = FIXED_FIELD_LEN * row_id * num_cols_ + FIXED_FIELD_LEN * col_id;
            auto val = *(int32_t*)(rows_ + offset);

            //如果col0 <= threshold则不满足条件，break
            if (col_id == 0 && val <= threshold) {
                break;
            }
            sum += val;
        }
    }
    
    return sum;
}

int64_t RowTable::PredicatedUpdate(int32_t threshold) {
    // TODO: Implement this!
    int64_t update_rows = 0;
    int32_t col_0 = 0;
    for (auto row_id = 0; row_id < num_rows_; row_id++) {
            //求col0,col2和col3的地址偏移量
            auto offset_c0 = FIXED_FIELD_LEN * row_id * num_cols_ + FIXED_FIELD_LEN * (col_0);
            auto offset_c2 = FIXED_FIELD_LEN * row_id * num_cols_ + FIXED_FIELD_LEN * (col_0 + 2);
            auto offset_c3 = FIXED_FIELD_LEN * row_id * num_cols_ + FIXED_FIELD_LEN * (col_0 + 3);

            //判断col0的值是否满足条件，不满足则continue
            int32_t val_c0 = *(int32_t*)(rows_ + offset_c0);
            if (val_c0 >= threshold) {
                continue;
            }
            //取出col2和col3的值
            int32_t val_c2 = *(int32_t*)(rows_ + offset_c2);
            int32_t val_c3 = *(int32_t*)(rows_ + offset_c3);

            //修改col3的数据(col3 = col2+ col3)
            *(int32_t*)(rows_ + offset_c3) = val_c2 + val_c3;

            //更新过的行数+1
            ++update_rows;
    }
    
    return update_rows;
}
} // namespace bytedance_db_project
