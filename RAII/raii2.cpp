#include <cstdlib>
#include <cstring>
#include <cstdio>

class string {
public:
    string(): m_data(nullptr), m_size(0) {}
    explicit string(const char* str): m_data(str), m_size(strlen(str)) {}
    string(const char* data, size_t size): m_data(data), m_size(size) {}
    const char* begin() const { return m_data; }
    const char* end() const { return m_data + m_size; }
private:
    const char* m_data;
    size_t m_size;
};

void print(const string& s) {
    for (auto itr = s.begin(); itr != s.end(); ++itr) {
        putchar(*itr);
    }
}

void print(const char* str) {
    print(string(str));
}

// void encrypt(string& s) {
//     for (auto itr = s.begin(); itr != s.end(); ++itr) {
//         ++*itr;
//     }
// }

int main() {
    string hello_msg("Hello, world!\n");
    print(hello_msg);
    print("This is a C string.\n");
}
