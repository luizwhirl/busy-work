#include <iostream>
#include <thread>
#include <vector>
#include <atomic>

void busy_work(std::atomic<bool>& running) {
    while (running.load()) {
        // operação pesada e inútil, essa que é a graça da coisa
        volatile double x = 0;
        for (int i = 0; i < 1000000; ++i) {
            x += std::sin(i) * std::tan(i);
        }
    }
}

int main() {
    const int num_threads = std::thread::hardware_concurrency();
    std::atomic<bool> running(true);
    std::vector<std::thread> threads;

    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(busy_work, std::ref(running));
    }

    std::cout << "pare com 'enter'\n";
    std::cin.get();

    running = false;
    for (auto& t : threads) {
        t.join();
    }

    std::cout << "encerrado\n";
    return 0;
}
