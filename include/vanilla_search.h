#ifndef VANILLA_SEARCH_H
#define VANILLA_SEARCH_H

#include <string>
#include <vector>

class VanillaSearch {
public:
    // Constructor that takes the unencoded data column
    explicit VanillaSearch(const std::vector<std::string>& data_column);

    // Exact match query: returns indices of the data item in the unencoded column
    std::vector<size_t> exactMatchQuery(const std::string& data_item) const;

    // Prefix match query: returns indices of data items that start with the prefix in the unencoded column
    std::vector<size_t> prefixMatchQuery(const std::string& prefix) const;

private:
    const std::vector<std::string>& data_column_; // Stores unencoded data for vanilla search
};

#endif // VANILLA_SEARCH_H
