#include <memory>
#include <iostream>
#include <span>

size_t get_config_buffer_size() {
    return 1024;
}

size_t c_alloc_and_init_buffer(char** pptr) {
    if (pptr) {
        size_t buffer_size = get_config_buffer_size();
        *pptr = (char*)malloc(buffer_size);
        if (!*pptr) {
            exit(EXIT_FAILURE);
        }
        (*pptr)[0] = 'a';
        return buffer_size;
    }
    return 0;
}

void c_use_buffer(const char* buffer, size_t size) {
    printf("buffer size: %zd\n", size);
    printf("first char: %c\n", buffer[0]);
}

void c_func() {
    char* buffer;
    size_t size = c_alloc_and_init_buffer(&buffer);
    c_use_buffer(buffer, size);
    free(buffer);
}

auto alloc_and_init_buffer() {
    auto size = get_config_buffer_size();
    auto ret = std::make_unique<char[]>(size);
    ret[0] = 'a';
    return std::make_tuple(std::move(ret), size);
}

auto use_buffer(std::span<const char> buffer) {
    std::cout << "buffer size: " << buffer.size() << std::endl;
    std::cout << "first char: " << buffer[0] << std::endl;
}

auto func() {
    auto [buffer, size] = alloc_and_init_buffer();
    use_buffer(std::span<char>(buffer.get(), size));
}

int main() {
    c_func();
    func();
}