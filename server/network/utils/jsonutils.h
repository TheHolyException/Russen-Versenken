#ifndef JSONUTILS_H
#define JSONUTILS_H

#include <string>
#include <sstream>
#include <map>
#include <variant> // std::get
#include <tuple> // std::get
#include <iostream> // std::cout

/**
 * @brief A class for generating JSON strings from a map of key-value pairs.
 */
class JSONUtils
{
public:
    /**
     * @brief Constructs a new JSONUtils object.
     */
    JSONUtils();

    /**
     * @brief A variant type that can hold int, bool, or std::string values.
     */
    using Value = std::variant<int, bool, std::string>;

    /**
     * @brief Generates a JSON string from the given data.
     * @param data A map of key-value pairs to include in the JSON string.
     * @return The generated JSON string.
     */
    static std::string generateJSON(const std::map<std::string, Value>& data);
};

#endif // JSONUTILS_H
