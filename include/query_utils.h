#ifndef QUERY_UTILS_H
#define QUERY_UTILS_H

#include <string>
#include <vector>

namespace QueryUtils {

// Function to check if a string starts with the given prefix using SIMD (AVX2)
bool startsWithSIMD(const std::string& str, const std::string& prefix);

// Exact Match Search using SIMD (AVX2)
bool exactMatchSIMD(const std::string& str, const std::string& target);

} // namespace QueryUtils

#endif // QUERY_UTILS_H
