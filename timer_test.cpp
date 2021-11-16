#include <iostream>
#include <chrono>
#include <mutex>
#include <thread>

#include "timer.h"

using namespace std;

int main()
{
    Timer timer;

    int index = 0;
    uint64_t id;
    std::mutex log_mutex;
    id = timer.setInterval([&]() {
        auto now = std::chrono::system_clock::now();
        auto t = std::chrono::system_clock::to_time_t(now);

        std::lock_guard<std::mutex> lock(log_mutex);
        cout << "interval 1.. time: " << t << " After each 1s..." << index++ << endl;
    }, 100);

    // will run lambda forever until timer is destroyed
    timer.setInterval([&]() {
        auto now = std::chrono::system_clock::now();
        auto t = std::chrono::system_clock::to_time_t(now);

        std::lock_guard<std::mutex> lock(log_mutex);
        cout << "interval 2.. time: " << t << " After each 1s..." << index++ << endl;
    }, 100);

    timer.setTimeout([&]() {
        auto now = std::chrono::system_clock::now();
        auto t = std::chrono::system_clock::to_time_t(now);

        std::lock_guard<std::mutex> lock(log_mutex);
        cout << "Hey.. time: " << t << " After 5.2s. But I will stop the timer!" << endl;
        timer.stop(id);
        }, 5200);

    auto now = std::chrono::system_clock::now();
    cout << "I am Timer, now is: " <<  std::chrono::system_clock::to_time_t(now) << endl;


    for(int i =0; i< 100; i++)
    {
        Timer timer2;
        int index2 = 0;
        // will not exec, because timer2 will be destroyed before lambda run
        timer2.setInterval([&]() {
            auto now = std::chrono::system_clock::now();
            auto t = std::chrono::system_clock::to_time_t(now);

            cout << "Hey Timer2.. time: " << t << " After each 1s..." << index2++ << endl;
        }, 1000);
    }

    std::getchar();
    return 0;
}
