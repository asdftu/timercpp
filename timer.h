#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

class Timer {
    static uint64_t index;
    static std::map<uint64_t, bool> active_map;
    static std::mutex mutex;

public:
    template<typename Function>
    uint64_t setTimeout(Function function, int delay);
    template<typename Function>
    uint64_t setInterval(Function function, int interval);
    void stop(const uint64_t& id);
};

uint64_t Timer::index = 100;
std::map<uint64_t,bool> Timer::active_map;
std::mutex Timer::mutex;


template<typename Function>
uint64_t Timer::setTimeout(Function function, int delay) {
    std::lock_guard<std::mutex> lock(mutex);
    const uint64_t id = index;
    active_map.insert(make_pair(id, true));
    index++;
    auto& active = active_map[id];
    std::thread t([function, delay, &active]() {
        if (!active.load()) return;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        if (!active.load()) return;
        function();
        });
    t.detach();
    return id;
}

template<typename Function>
uint64_t Timer::setInterval(Function function, int interval) {
    std::lock_guard<std::mutex> lock(mutex);
    const uint64_t id = index;
    active_map.insert(make_pair(id, true));
    index++;
    auto& active = active_map[id];
    std::thread t([function, interval, &active]() {
        while (active.load()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
            if (!active.load()) return;
            function();
        }
        });
    t.detach();
    return id;
}

void Timer::stop(const uint64_t& id) {
    std::lock_guard<std::mutex> lock(mutex);
    if (active_map.find(id) != active_map.end())
    {
        active_map[id] = false;
    }
}

