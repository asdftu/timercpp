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
t.setTimeout([&]() {
    cout << "Hey.. After 1s." << endl;
}, 1000); 
```

## `setInterval(auto function, int interval)`

```c++
Timer t = Timer();
t.setInterval([&]() {
    cout << "Hey.. After each 1s..." << endl;
}, 1000); 
```

## Sample Program

```c++
#include <iostream>
#include "timercpp.h"

using namespace std;

int main() {
    Timer t = Timer();

    t.setInterval([&]() {
        cout << "Hey.. After each 1s..." << endl;
    }, 1000); 

    t.setTimeout([&]() {
        cout << "Hey.. After 5.2s. But I will stop the timer!" << endl;
        t.stop();
    }, 5200); 

    

    cout << "I am Timer" <<endl;


    while(true); // Keep main thread active
}
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
g++ sample.cpp -std=c++14 -pthread
```

### License

[MIT](https://github.com/shalithasuranga/timercpp/edit/master/LICENSE)
