#include "timer.h"

uint64_t Timer::index = 100;
std::map<uint64_t, bool> Timer::active_map;
std::mutex Timer::mutex;

Timer::~Timer()
{
    for (auto& id : ids)
    {
        stop(id);
    }
}

void Timer::stop(const uint64_t& id) {
    std::lock_guard<std::mutex> lock(mutex);
    if (active_map.find(id) != active_map.end())
    {
        active_map[id] = false;
    }
}

