#ifndef QUERY_UTILS_H
#define QUERY_UTILS_H

#include <string>
#include <vector>

namespace QueryUtils {
    // Checks if str starts with the given prefix using SIMD
    bool startsWithSIMD(const std::string& str, const std::string& prefix);
}

#endif // QUERY_UTILS_H
