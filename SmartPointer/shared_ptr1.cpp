#include <thread>
#include <memory>
#include <iostream>
#include <atomic>
#include <vector>
#include <chrono>
#include <mutex>

using namespace std::chrono_literals;

std::mutex cout_mutex;
#define COUT { std::lock_guard<std::mutex> lg(cout_mutex); std::cout
#define ENDL std::endl; } do {} while(false)

auto spawn(int concurrency) {
    auto counter = std::make_shared<std::atomic<int>>(0);
    std::vector<std::thread> vec_thrds;
    for (int i = 0; i < concurrency; ++i) {
        vec_thrds.emplace_back([=](){
            std::this_thread::sleep_for(1s); // simulate per thread work
            COUT << "thread " << std::this_thread::get_id() << " done" << ENDL;
            if (counter->fetch_add(1, std::memory_order_relaxed) == concurrency - 1) {
                COUT << "last thread!" << ENDL;
                COUT << counter.use_count() << " instance is still alive" << ENDL;
            }
        });
    }
    return vec_thrds;
}

int main() {
    auto thrds = spawn(10);
    std::this_thread::sleep_for(2s); // simulate main thread work
    COUT << "main thread done" << ENDL;
    for (auto& thrd: thrds) {
        thrd.join();
    }
}