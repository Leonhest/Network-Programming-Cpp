#include <iostream>
#include "Workers.h"


int main() {
    int numWork = 4;

    Workers workers(numWork);
    workers.post([] {
        cout << "The" << endl;
    });
    workers.post([] {
        cout << "cake" << endl;
    });
    workers.post([] {
        cout << "is" << endl;
    });
    workers.start();
    workers.post([] {
        cout << "a" << endl;
    });
    workers.post([] {
        cout << "lie" << endl;
    });
    workers.joinThreads();

    return 0;
}
