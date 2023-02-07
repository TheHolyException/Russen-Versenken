#include "jsonutils.h"

JSONUtils::JSONUtils()
{

}

std::string JSONUtils::generateJSON(const std::map<std::string, Value>& data) {
    std::stringstream json;
    json << "{";
    for (const auto& [key, value] : data) {
      json << "\"" << key << "\":";
      // Use a switch statement to handle different data types for the value
      switch (value.index()) {
        case 0: // int
          json << std::get<int>(value);
          break;
        case 1: // bool
          json << (std::get<bool>(value) ? "true" : "false");
          break;
        case 2: // std::string
          json << "\"" << std::get<std::string>(value) << "\"";
          break;
      }
      json << ", ";
    }
    // Remove the last comma and newline before closing the object
    json.seekp(-2, std::ios_base::end);
    json << "}";
    return json.str();
  }
