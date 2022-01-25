#include <memory>
#include <iostream>

FILE* c_open_config_file() {
    return fopen("config.txt", "w");
}

void c_write_config(FILE* fp) {
    fprintf(fp, "buffer_size = 1024\n");
}

void c_func() {
    FILE* file = c_open_config_file();
    c_write_config(file);
    fclose(file);
}

auto open_config_file() {
    return std::unique_ptr<FILE, std::decay_t<decltype(fclose)>>(fopen("config.txt", "w"), fclose);
}

auto write_config(FILE* fp) {
    fprintf(fp, "buffer_size = 1024\n");
}

auto func() {
    auto ret = open_config_file();
    write_config(ret.get());
}

int main() {
    c_func();
    func();
}