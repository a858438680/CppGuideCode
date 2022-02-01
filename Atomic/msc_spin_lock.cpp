#include <atomic>
#include <thread>
#include <vector>
#include <cassert>

class spin_lock {
public:
    struct lock_node {
        std::atomic<lock_node*> next;
        std::atomic<int> locked;
    };

    spin_lock(): tail(nullptr) {}

    void lock(lock_node* node) {
        node->next.store(nullptr, std::memory_order_relaxed);
        node->locked.store(0, std::memory_order_relaxed);

        auto prev = tail.exchange(node, std::memory_order_relaxed);
        if (not prev) {
            return;
        }

        prev->next.store(node, std::memory_order_relaxed);
        while(node->locked.load(std::memory_order_acquire) == 0);
    }

    void unlock(lock_node* node) {
        auto next = node->next.load(std::memory_order_relaxed);
        if (not next) {
            auto desired = node;
            if (tail.compare_exchange_strong(
                desired,
                nullptr,
                std::memory_order_release,
                std::memory_order_relaxed)
            ) {
                return;
            }

            while ((next = node->next.load(std::memory_order_relaxed)) == nullptr);
        }

        next->locked.store(1, std::memory_order_release);
    }
private:
    std::atomic<lock_node*> tail;
};

constexpr auto concurrent = 16;
constexpr auto work_per_thread = 100000;

spin_lock lock;
int counter = 0;

auto add() {
    for (int i = 0; i < work_per_thread; ++i) {
        spin_lock::lock_node node;
        lock.lock(&node);
        ++counter;
        lock.unlock(&node);
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