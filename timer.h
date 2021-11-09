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
    static uint64_t index;
    static std::map<uint64_t, bool> active_map;
    static std::mutex mutex;

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
    std::lock_guard<std::mutex> lock(mutex);
    const uint64_t id = index;
    ids.push_back(id);
    //auto pair = std::pair<uint64_t, bool>(id, true);
    //active_map.insert(pair);
    active_map.insert(std::pair<uint64_t, bool>(id, true));
    index++;
    auto& active = active_map[id];
    std::thread t([function, delay, &active]() {
        if (!active) return;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        if (!active) return;
        function();
        });
    t.detach();
    return id;
}

template<typename Function>
uint64_t Timer::setInterval(Function function, int interval) {
    std::lock_guard<std::mutex> lock(mutex);
    const uint64_t id = index;
    ids.push_back(id);
    active_map.insert(std::pair<uint64_t, bool>(id, true));
    index++;
    auto& active = active_map[id];
    std::thread t([function, interval, &active]() {
        while (active) {
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
            if (!active) return;
            function();
        }
        });
    t.detach();
    return id;
}


