#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>

std::mutex mtx;
std::atomic<int> counter(0);

void increment()
{
    for (int i = 0; i < 10000; ++i)
    {
        std::lock_guard<std::mutex> lock(mtx);
        counter++;
    }
}

int main()
{
    std::thread t1(increment);
    std::thread t2(increment);

    t1.join();
    t2.join();

    std::cout << "Counter value: " << counter << std::endl;

    return 0;
}
