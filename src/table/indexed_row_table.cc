#include "indexed_row_table.h"
#include<vector>
#include<cstring>
namespace bytedance_db_project {
IndexedRowTable::IndexedRowTable(int32_t index_column) {
  index_column_ = index_column;
}

void IndexedRowTable::Load(BaseDataLoader* loader) {
    // TODO: Implement this!
    num_cols_ = loader->GetNumCols();
    auto rows = loader->GetRows();
    num_rows_ = rows.size();
    rows_ = new char[FIXED_FIELD_LEN * num_rows_ * num_cols_];
    index_.resize(num_cols_);
    for (auto row_id = 0; row_id < num_rows_; row_id++) {
        auto cur_row = rows.at(row_id);
        for (auto col_id = 0; col_id < num_cols_; col_id++) {

            //先取列值，再加入该列的索引，最后写入rows_
            int32_t value = *(int32_t*)(cur_row + col_id * FIXED_FIELD_LEN);
            auto &cur_index = index_[col_id].index;
            cur_index[value].emplace_back(row_id);
            int32_t offset = FIXED_FIELD_LEN * ((row_id * num_cols_) + col_id);
            std::memcpy(rows_ +offset, cur_row+FIXED_FIELD_LEN * col_id,
                FIXED_FIELD_LEN);
        }
    }
}

int32_t IndexedRowTable::GetIntField(int32_t row_id, int32_t col_id) {
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

void IndexedRowTable::PutIntField(int32_t row_id, int32_t col_id,int32_t field) {
    // TODO: Implement this!
     //首先计算偏移量
    auto offset = FIXED_FIELD_LEN * row_id * num_cols_ + FIXED_FIELD_LEN * col_id;

    //cur_index为该列的map索引
    auto &cur_index = index_[col_id].index;

    //判断偏移量是否在合法范围内
    if (offset >= 0 && offset < FIXED_FIELD_LEN * num_rows_ * num_cols_) {

        //对索引进行修改
        cur_index[field].emplace_back(row_id);
        int32_t val = *(int32_t*)(rows_ + offset);
        std::vector<int32_t> &row_id_group = cur_index[val];
        for (auto i = 0; i < (int32_t)row_id_group.size(); i++) {
            if (row_id_group[i] == row_id) {
                row_id_group.erase(row_id_group.begin() + i);
                break;
            }
        }

        //通过偏移量获取对应int32_t类型的数据并赋值为field
        *(int32_t*)(rows_ + offset) = field;
    }
}

int64_t IndexedRowTable::ColumnSum() {
    // TODO: Implement this!
    int64_t sum = 0;

    for (auto row_id = 0; row_id < num_rows_; row_id++) {

        //col0所在地址的偏移量
        auto offset = FIXED_FIELD_LEN * row_id*num_cols_;
        sum += *(int32_t*)(rows_ + offset);
    }
    return sum;
}

int64_t IndexedRowTable::PredicatedColumnSum(int32_t threshold1,int32_t threshold2) {
    // TODO: Implement this!
    int64_t sum = 0;
    int32_t col0 = 0, col1 = 1, col2 = 2;
    if (num_cols_ >= 3) {
        //先利用索引获取满足col1>threshold1的row_id
        std::vector<int32_t>row_id_group = index_[col1].GetGreaterRowId(threshold1);

        //遍历vector依次判断每个row_id的col2是否满足条件，满足则取col0的值加入sum
        for (auto row_id : row_id_group) {
            auto offset_c2 = row_id * num_cols_ * FIXED_FIELD_LEN + col2 * FIXED_FIELD_LEN;
            auto val_c2 = *(int32_t*)(rows_ + offset_c2);
            if (val_c2 < threshold2) {
                auto offset_c0 = row_id * num_cols_ * FIXED_FIELD_LEN + col0 * FIXED_FIELD_LEN;
                auto val_c0 = *(int32_t*)(rows_ + offset_c0);
                sum += val_c0;
            }
        }
    }

    return sum;
}

int64_t IndexedRowTable::PredicatedAllColumnsSum(int32_t threshold) {
    // TODO: Implement this!
    int64_t sum = 0;
    int32_t col0 = 0;
    //利用索引得出所有满足col0>threshold条件的row_id
    std::vector<int32_t>row_id_group = index_[col0].GetGreaterRowId(threshold);
    for (auto row_id : row_id_group) {
        for (auto col_id = 0; col_id < num_cols_; col_id++) {
            auto offset = FIXED_FIELD_LEN * row_id * num_cols_ + FIXED_FIELD_LEN * col_id;
            auto val = *(int32_t*)(rows_ + offset);
            sum += val;
        }
    }
    return sum;
}

int64_t IndexedRowTable::PredicatedUpdate(int32_t threshold) {
    // TODO: Implement this!
    int64_t update_rows = 0;
    int32_t col0 = 0, col2 = 2, col3 = 3;

    //利用索引获取满足col0<threshold的所有row_id
    std::vector<int32_t>row_id_group = index_[col0].GetLessRowId(threshold);
    for (auto row_id:row_id_group) {
        //求col2和col3的地址偏移量
        auto offset_c2 = FIXED_FIELD_LEN * row_id * num_cols_ + FIXED_FIELD_LEN * (col2);
        auto offset_c3 = FIXED_FIELD_LEN * row_id * num_cols_ + FIXED_FIELD_LEN * (col3);

        //取出col2和col3的值
        int32_t val_c2 = *(int32_t*)(rows_ + offset_c2);
        int32_t val_c3 = *(int32_t*)(rows_ + offset_c3);
        int32_t new_val = val_c2 + val_c3;

        //修改col3的数据(col3 = col2+ col3)
        *(int32_t*)(rows_ + offset_c3) = new_val;
        index_[col3].index[new_val].emplace_back(row_id);
        auto &col3_row_id_group=index_[col3].index[val_c3];
        for (auto cur_row_id = 0; cur_row_id < (int32_t)col3_row_id_group.size();cur_row_id++) {
            if (cur_row_id == row_id) {
                col3_row_id_group.erase(col3_row_id_group.begin()+cur_row_id);
                break;
            }
        }

        //更新过的行数+1
        ++update_rows;
    }

    return update_rows;
}

} // namespace bytedance_db_project