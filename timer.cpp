#include "timer.h"
#include <limits>

// TIMER_ID will forever > 0
const int TIMER_START_ID = 1;

std::atomic<uint64_t> Timer::index(TIMER_START_ID);
std::map<uint64_t, std::atomic_bool> Timer::active_map;
std::mutex Timer::mutex;
uint64_t Timer::getTimerId()
{
    static uint64_t max = std::numeric_limits<uint64_t>::max();
    uint64_t id = index.load() % max;
    if (id == 0)
    {
        id = 1;
    }
    index++;
    return id;
}

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

