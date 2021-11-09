#include "timer.h"

uint64_t Timer::index = 100;
std::map<uint64_t,std::atomic<bool>> Timer::active_map;
std::mutex Timer::mutex;
