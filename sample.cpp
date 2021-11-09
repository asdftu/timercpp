#include <iostream>
#include "timer.h"

using namespace std;

int main() {
    Timer t;

    t.setInterval([&]() {
        cout << "Hey.. After each 1s..." << endl;
    }, 1000); 

    uint64_t id;
    id = t.setTimeout([&]() {
        cout << "Hey.. After 5.2s. But I will stop the timer!" << endl;
        t.stop(id);
    }, 5200); 

    

    cout << "I am Timer" <<endl;


    while(true); // Keep mail thread active
}
