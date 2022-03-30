#include <utility>
#include "add.h"

template <>
std::string add<std::string>(std::string a, std::string b) {
    return a.append(std::move(b));
}