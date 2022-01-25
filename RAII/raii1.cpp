#include <cstdlib>
#include <cstring>
#include <cstdio>

class string {
public:
    string(): m_data(nullptr), m_size(0) {}
    string(char* str): m_data(str), m_size(strlen(str)) {}
    string(char* data, size_t size): m_data(data), m_size(size) {}
    char* begin() const { return m_data; }
    char* end() const { return m_data + m_size; }
private:
    char* m_data;
    size_t m_size;
};

void print(const string& s) {
    for (auto itr = s.begin(); itr != s.end(); ++itr) {
        putchar(*itr);
    }
}

// void print(const char* str) {
//     print(string(str));
// }

int main() {
    // string hello_msg("Hello, world!");
}