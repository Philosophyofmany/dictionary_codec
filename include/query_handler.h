#ifndef QUERY_HANDLER_H
#define QUERY_HANDLER_H

#include <string>
#include <vector>
#include <unordered_map>

class QueryHandler {
public:
    // Constructor to initialize the dictionary, encoded data, and index map
    QueryHandler(const std::unordered_map<std::string, int>& dictionary, const std::vector<int>& encoded_data);

    // Exact match query with SIMD optimization: returns indices of the data item
    std::vector<size_t> exactMatchQuery(const std::string& data_item) const;

    // Prefix match query with SIMD optimization: returns indices of data items that start with the prefix
    std::vector<size_t> prefixMatchQuery(const std::string& prefix) const;

    // Exact match query without SIMD: returns indices of the data item
    std::vector<size_t> exactMatchQueryNoSIMD(const std::string& data_item) const;

    // Prefix match query without SIMD: returns indices of data items that start with the prefix
    std::vector<size_t> prefixMatchQueryNoSIMD(const std::string& prefix) const;

    // Returns the duration of the last query in microseconds
    long long getLastQueryDuration() const { return last_query_duration_; }

private:
    // Member variables
    const std::unordered_map<std::string, int>& dictionary_;
    const std::vector<int>& encoded_data_;
    std::unordered_map<int, std::vector<size_t>> data_index_; // Map from encoded value to indices

    mutable long long last_query_duration_;
};

#endif // QUERY_HANDLER_H
