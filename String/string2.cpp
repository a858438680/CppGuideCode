#include <cstdlib>
#include <cstring>
#include <cstdio>

class string {
public:
    string() : m_size(0), m_capacity(1), m_data(new char[1]) {
        m_data[0] = '\0';
    }
    string(const char* str): m_size(strlen(str)), m_capacity(m_size + 1), m_data(new char[m_capacity]) {
        memcpy(m_data, str, m_capacity);
    }
    string(const char* data, size_t size): m_size(size), m_capacity(m_size + 1), m_data(new char[m_capacity]) {
        memcpy(m_data, data, m_size);
        m_data[m_size] = '\0';
    }
    string(const string& x): m_size(x.m_size), m_capacity(m_size + 1), m_data(new char[m_capacity]) {
        memcpy(m_data, x.m_data, m_capacity);
    }
    string(string&& x): m_size(x.m_size), m_capacity(x.m_capacity), m_data(x.m_data) {
        x.m_data = nullptr;
    }
    string& operator=(const string& rhs) {
        size_t new_size = rhs.m_size;
        size_t new_capacity = new_size + 1;
        char *new_data = new char[new_capacity];
        memcpy(new_data, rhs.m_data, new_capacity);
        delete [] m_data;
        m_size = new_size;
        m_capacity = new_capacity;
        m_data = new_data;
        return *this;
    }
    string& operator=(string&& rhs) {
        delete [] m_data;
        m_size = rhs.m_size;
        m_capacity = rhs.m_capacity;
        m_data = rhs.m_data;
        rhs.m_data = nullptr;
        return *this;
    }
    void push_back(char c) {
        may_alloc_capacity(m_size + 1);
        m_data[m_size] = c;
        ++m_size;
        m_data[m_size] = '\0';
    }
    void pop_back() {
        if (m_size > 0) {
            --m_size;
            m_data[m_size] = '\0';
        }
    }
    char* c_str() {
        return m_data;
    }
    const char* c_str() const {
        return m_data;
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
    size_t m_capacity;
    char* m_data;

    void may_alloc_capacity(size_t size) {
        if (size + 1 <= m_capacity) {
            return;
        }
        size_t new_capacity = m_capacity + m_capacity / 2;
        new_capacity = (size + 1 > new_capacity) ? (size + 1) : new_capacity;
        char *new_data = new char[new_capacity];
        memcpy(new_data, m_data, m_size);
        delete [] m_data;
        m_capacity = new_capacity;
        m_data = new_data;
    }
};

void itoa_impl(int i, string& s) {
    if (i != 0) {
        itoa_impl(i / 10, s);
        int digit = i % 10;
        digit = digit > 0 ? digit : -digit;
        s.push_back('0' + digit);
    }
}

string itoa(int i) {
    if (i == 0) return string("0");
    string ret;
    if (i < 0) {
        ret.push_back('-');
    }
    itoa_impl(i, ret);
    return ret;
}

int main() {
    printf("%s\n", itoa(0).c_str());
    printf("%s\n", itoa(1).c_str());
    printf("%s\n", itoa(-1).c_str());
    printf("%s\n", itoa(10).c_str());
    printf("%s\n", itoa(-20).c_str());
    printf("%s\n", itoa(-100).c_str());
    printf("%s\n", itoa(0x7fffffff).c_str());
    printf("%s\n", itoa(0x80000000).c_str());
}