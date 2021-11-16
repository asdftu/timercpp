#pragma once

#include <iostream>
#include <thread>
#include <chrono>
#include <map>
#include <mutex>
#include <vector>
#include <atomic>
#include <utility>

class Timer {
    static std::atomic<uint64_t> index;
    static std::map<uint64_t, std::atomic_bool> active_map;
    static std::mutex mutex;
    static uint64_t getTimerId();

public:
    Timer() {}
    virtual ~Timer();
    Timer(const Timer& t) = delete;
    Timer operator =(const Timer& t) = delete;


public:
    template<typename Function>
    uint64_t setTimeout(Function function, int delay);
    template<typename Function>
    uint64_t setInterval(Function function, int interval);
    void stop(const uint64_t& id);
private:
    std::vector<uint64_t> ids;
};

template<typename Function>
uint64_t Timer::setTimeout(Function function, int delay) {
    const uint64_t id = getTimerId();
    std::lock_guard<std::mutex> lock(mutex);
    ids.push_back(id);
    active_map[id] = true;
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
    const uint64_t id = getTimerId();
    std::lock_guard<std::mutex> lock(mutex);
    ids.push_back(id);
    active_map[id] = true;
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


