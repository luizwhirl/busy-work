#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <cmath>
#include <random>
#include <chrono>

void intense_cpu_work(std::atomic<bool>& running, int thread_id) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1000.0);
    
    // criando operações pesadas
    volatile double result1 = 0, result2 = 0, result3 = 0;
    volatile long long counter = 0;
    
    while (running.load()) {
        // Loop interno muito maior para mais processamento
        for (int i = 0; i < 2000000; ++i) {
            double x = dis(gen);
            
            // continhas desnecessárias
            result1 += std::sin(x) * std::cos(x) * std::tan(x);
            result2 += std::exp(std::log(x + 1)) * std::sqrt(x);
            result3 += std::pow(x, 0.5) * std::atan(x);
            
            // e uns float pra encher o sako
            volatile double temp = std::sinh(x) * std::cosh(x);
            temp = std::log10(temp + 1) * std::ceil(x);
            
            counter++;
            
            if (i % 100000 == 0) {
                for (int j = 0; j < 10000; ++j) {
                    volatile double waste = std::gamma(j % 10 + 1);
                    waste = std::lgamma(waste);
                }
            }
        }
        
        volatile int* dummy_array = new int[10000];
        for (int k = 0; k < 10000; ++k) {
            dummy_array[k] = k * k;
        }
        delete[] dummy_array;
    }
    
    std::cout << "Thread " << thread_id << " processou " << counter << " operações\n";
}

void memory_pressure(std::atomic<bool>& running) {
    std::vector<std::vector<double>> memory_waster;
    
    while (running.load()) {
        memory_waster.push_back(std::vector<double>(100000, 3.14159));
        
        if (memory_waster.size() > 50) {
            memory_waster.clear();
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

int main() {
    std::cout << "=== STRESS TEST INTENSO DE CPU ===\n";
    std::cout << "ALERTA: esse programa vai deixar o sistema MUITO lento\n";
    std::cout << "pressione enter para continuar ou ctrl + c para cancelar\n";
    std::cin.get();
    
    const int num_cpu_threads = std::thread::hardware_concurrency() * 2;
    std::atomic<bool> running(true);
    std::vector<std::thread> threads;
    
    std::cout << "Iniciando " << num_cpu_threads << " threads de CPU + 1 thread de memória...\n";
    
    for (int i = 0; i < num_cpu_threads; ++i) {
        threads.emplace_back(intense_cpu_work, std::ref(running), i);
    }
    
    threads.emplace_back(memory_pressure, std::ref(running));
    
    std::cout << "\nstress máximo de sistema alçancado\n";
    std::cout << "pressione enter pra parar\n";
    std::cin.get();
    
    std::cout << "parano threads\n";
    running = false;
    
    for (auto& t : threads) {
        t.join();
    }
    
    std::cout << "teste de stress encerrado - nunca mais repita isso\n";
    return 0;
}
