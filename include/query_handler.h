#ifndef QUERY_HANDLER_H
#define QUERY_HANDLER_H

#include <string>
#include <vector>
#include <unordered_map>

class QueryHandler {
public:
    QueryHandler(const std::unordered_map<std::string, int>& dictionary, const std::vector<int>& encoded_data);

    // Exact match query: returns indices of the data item
    std::vector<size_t> exactMatchQuery(const std::string& data_item) const;

    // Prefix match query: returns indices of data items that start with the prefix
    std::vector<size_t> prefixMatchQuery(const std::string& prefix) const;

private:
    const std::unordered_map<std::string, int>& dictionary_;
    const std::vector<int>& encoded_data_;
    std::unordered_map<int, std::vector<size_t>> data_index_; // Map from encoded value to indices
};

#endif // QUERY_HANDLER_H
