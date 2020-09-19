#include "string.h"

std::string to_lower(const std::string& original)
{
    if(!original.size()) return std::string();

    std::string result = original;
    auto it = result.begin();
    auto end = result.end();

    while(it != end){
        *it = std::tolower(*it);
        it++;
    }

    return result;
}

bool is_path_separator(const char chr)
{
    return (chr == '\\' || chr == '/');
}