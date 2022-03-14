#pragma once
#include "data/csv_data_loader.h"
#include <map>
#include <vector>
namespace bytedance_db_project {

//列索引结构体
struct Col_Index {

    //rbt索引，key为列值，value为行id
    std::map<int32_t, std::vector<int32_t>> index;

    //索引查找该列中列值大于参数val的所有行id，并返回包含所有行id的vector
    std::vector<int32_t> GetGreaterRowId(int32_t val) {
        std::vector<int32_t> result;
        auto it = index.upper_bound(val);
        for (; it != index.end(); it++) {
            auto row_id_group = it->second;
            for (auto row_id : row_id_group) {
                result.emplace_back(row_id);
            }
        }
        return result;
    }

    //索引查找该列中列值大于等于参数val的所有行id，并返回包含所有行id的vector
    std::vector<int32_t> GetGreaterOrEqualedRowId(int32_t val) {
        std::vector<int32_t> result;
        auto it = index.lower_bound(val);
        for (; it != index.end(); it++) {
            auto row_id_group = it->second;
            for (auto row_id : row_id_group) {
                result.emplace_back(row_id);
            }
        }

        return result;
    }

    //索引查找该列中列值小于参数val的所有行id，并返回包含所有行id的vector
    std::vector<int32_t> GetLessRowId(int32_t val) {
        std::vector<int32_t> result;
        for (auto it : index) {
            auto cur_val = it.first;
            if (cur_val >= val) break;
            auto row_id_group = it.second;
            for (auto row_id : row_id_group) {
                result.emplace_back(row_id);
            }
        }
        return result;
    }

    //索引查找该列中列值小于等于参数val的所有行id，并返回包含所有行id的vector
    std::vector<int32_t> GetLessOrEqualedRowId(int32_t val) {
        std::vector<int32_t> result;
        for (auto it : index) {
            auto cur_val = it.first;
            if (cur_val > val) break;
            auto row_id_group = it.second;
            for (auto row_id : row_id_group) {
                result.emplace_back(row_id);
            }
        }
        return result;
    }
};
class Table {
public:
    // Loads data into the table through passed-in data loader. Is not timed.
    virtual void Load(BaseDataLoader *loader) = 0;

    // Returns the int32_t field at row `row_id` and column `col_id`.
    virtual int32_t GetIntField(int32_t row_id, int32_t col_id) = 0;

    // Inserts the passed-in int32_t field at row `row_id` and column `col_id`.
    virtual void PutIntField(int32_t row_id, int32_t col_id, int32_t field) = 0;

    // Implements the query
    // SELECT SUM(col0) FROM table;
    // Returns the sum of all elements in the first column of the table.
    virtual int64_t ColumnSum() = 0;

    // Implements the query
    // SELECT SUM(col0) FROM table WHERE col1 > threshold1 AND col2 < threshold2;
    // Returns the sum of all elements in the first column of the table,
    // subject to the passed-in predicates.
    virtual int64_t PredicatedColumnSum(int32_t threshold1,
                                        int32_t threshold2) = 0;

    // Implements the query
    // SELECT SUM(col0) + SUM(col1) + ... + SUM(coln) FROM table WHERE col0 >
    // threshold; Returns the sum of all elements in the rows which pass the
    // predicate.
    virtual int64_t PredicatedAllColumnsSum(int32_t threshold) = 0;

    // Implements the query
    // UPDATE(col3 = col3 + col2) WHERE col0 < threshold;
    // Returns the number of rows updated.
    virtual int64_t PredicatedUpdate(int32_t threshold) = 0;
};
} // namespace bytedance_db_project
