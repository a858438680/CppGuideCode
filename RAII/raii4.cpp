#include <cstdlib>
#include <cstring>
#include <cstdio>

class string {
public:
    string(const char* str): m_size(strlen(str)), m_data(new char[m_size]) {
        memcpy(m_data, str, m_size);
    }
    string(const char* data, size_t size): m_size(size), m_data(new char[m_size]){
        memcpy(m_data, data, m_size);
    }
    ~string() {
        delete [] m_data;
    }
    const char* begin() const { return m_data; }
    const char* end() const { return m_data + m_size; }
    char* begin() { return m_data; }
    char* end() { return m_data + m_size; }
private:
    size_t m_size;
    char* m_data;
};

void print(const string& s) {
    for (auto itr = s.begin(); itr != s.end(); ++itr) {
        putchar(*itr);
    }
}

void print(const char* str) {
    print(string(str));
}

void encrypt(string& s) {
    for (auto itr = s.begin(); itr != s.end(); ++itr) {
        ++*itr;
    }
}

int main() {
    string hello_msg("Hello, world!\n");
    print(hello_msg);
    print("This is a C string.\n");

    string alphabet("abcde");
    string alphabet2 = alphabet;
    encrypt(alphabet2);
    print(alphabet);
    print("\n");
    print(alphabet2);
    print("\n");
}
