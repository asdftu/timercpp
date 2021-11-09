Fork from [99x/timercpp](https://github.com/99x/timercpp)


fix the issues which are not fixed

* use templete function instead of 'auto' [aut is not Allowed #3](https://github.com/99x/timercpp/issues/3)
* store the active in static field, avoid invalid memory access when Timer is destroyed [Read access violation after leaving scope #5](https://github.com/99x/timercpp/issues/5)
* add lock for thread-safe



# timercpp
Javascript like timer for c++ developers

This header only library has js equivalent `setTimeout()` and `setInterval()` for c++.

**DISCLAIMER - This implementation uses threads not a queue**

## `setTimeout(auto function, int delay)`

```c++
Timer t = Timer();
auto id = t.setTimeout([&]() {
    cout << "Hey.. After 1s." << endl;
}, 1000); 
//t.stop(id);
```

## `setInterval(auto function, int interval)`

```c++
Timer t = Timer();
auto id = t.setInterval([&]() {
    cout << "Hey.. After each 1s..." << endl;
}, 1000); 
//t.stop(id);
```

**Output**

```
I am Timer
Hey.. After each 1s...
Hey.. After each 1s...
Hey.. After each 1s...
Hey.. After each 1s...
Hey.. After each 1s...
Hey.. After 5.2s. But I will stop the timer!
```

### How to compile sample program?

```bash
g++ sample.cpp timer.cpp -std=c++11
```

### License

[MIT](https://github.com/shalithasuranga/timercpp/edit/master/LICENSE)
