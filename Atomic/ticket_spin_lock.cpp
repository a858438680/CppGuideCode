#include <atomic>
#include <thread>
#include <vector>
#include <cassert>

class spin_lock {
public:
    spin_lock(): head(0), tail(0) {}

    void lock() {
        auto ticket = tail.fetch_add(1, std::memory_order_relaxed);
        while (head.load(std::memory_order_acquire) != ticket);
    }

    void unlock() {
        head.fetch_add(1, std::memory_order_release);
    }
private:
    std::atomic<int> head;
    std::atomic<int> tail;
};

constexpr auto concurrent = 16;
constexpr auto work_per_thread = 100000;

spin_lock lock;
int counter = 0;

auto add() {
    for (int i = 0; i < work_per_thread; ++i) {
        lock.lock();
        ++counter;
        lock.unlock();
    }
}

int main() {
    std::vector<std::thread> thrds;
    for (int i = 0; i < concurrent; ++i) {
        thrds.emplace_back(add);
    }
    for (auto& thrd: thrds) {
        thrd.join();
    }
    assert(counter == concurrent * work_per_thread);
}