#include <atomic>
#include <thread>
#include <cassert>

std::atomic<int> a{0};
int b = 0;

int main() {
    auto t1 = std::thread([](){
        b = 1;
        a.store(1, std::memory_order_release);
    });

    auto t2 = std::thread([](){
        while (!a.load(std::memory_order_acquire));
        assert(b == 1);
    });

    t1.join(), t2.join();
}