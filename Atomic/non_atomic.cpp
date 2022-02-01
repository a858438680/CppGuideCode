#include <thread>
#include <vector>
#include <cassert>

int counter = 0;

auto add_1000() {
    for (int i = 0; i < 10000; ++i) {
        ++counter;
    }
}

int main() {
    std::vector<std::thread> thrds;
    for (int i = 0; i < 10; ++i) {
        thrds.emplace_back(add_1000);
    }
    for (auto& thrd: thrds) {
        thrd.join();
    }
    assert(counter == 100000);
}