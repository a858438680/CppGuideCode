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