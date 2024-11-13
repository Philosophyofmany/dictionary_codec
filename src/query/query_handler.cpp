#include "../../include/query_handler.h"
#include "../../include/query_utils.h"
#include <immintrin.h> // For SIMD instructions

// Constructor to initialize the dictionary, encoded data, and index map
QueryHandler::QueryHandler(const std::unordered_map<std::string, int>& dictionary, const std::vector<int>& encoded_data)
    : dictionary_(dictionary), encoded_data_(encoded_data) {
    // Build an index map for quick lookup of data item positions
    for (size_t i = 0; i < encoded_data.size(); ++i) {
        data_index_[encoded_data[i]].push_back(i);
    }
}

// Exact match query
std::vector<size_t> QueryHandler::exactMatchQuery(const std::string& data_item) const {
    std::vector<size_t> result;

    auto it = dictionary_.find(data_item);
    if (it != dictionary_.end()) {
        int encoded_value = it->second;
        if (data_index_.count(encoded_value)) {
            result = data_index_.at(encoded_value); // Get all indices of the exact match
        }
    }
    return result;
}

// Prefix match query with SIMD optimization
std::vector<size_t> QueryHandler::prefixMatchQuery(const std::string& prefix) const {
    std::vector<size_t> result;

    for (const auto& [data_item, encoded_value] : dictionary_) {
        if (QueryUtils::startsWithSIMD(data_item, prefix)) {
            if (data_index_.count(encoded_value)) {
                const auto& indices = data_index_.at(encoded_value);
                result.insert(result.end(), indices.begin(), indices.end());
            }
        }
    }
    return result;
}
