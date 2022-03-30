#include <string>

template <typename T>
T add(T a, T b) {
    return a + b;
}

extern template int add(int, int);
template <> std::string add<std::string>(std::string, std::string);