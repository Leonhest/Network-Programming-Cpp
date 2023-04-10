#include <iostream>
#include <vector>
#include <thread>
#include "PrimeFinder.h"
#include <cmath>

using namespace std;


int main() {
    int start = 999;
    int end = 2000;
    int numThreads = 11;
    int interval = ceil(float((end - start)) / float(numThreads));

    mutex list_lock;

    vector<int> primeList;

    vector<thread> threadList;
    threadList.reserve(numThreads);

    threadList.emplace_back([&, start, interval] {
        PrimeFinder::findPrimes(primeList, start,  start + interval, list_lock);
    });
    for (int i = 1; i < numThreads; i++){
        if(start + interval+interval*i > end){
            threadList.emplace_back([&, start, interval, i] {
                PrimeFinder::findPrimes(primeList, start + interval * i + 1,  end, list_lock);
            });
            break;
        }
        threadList.emplace_back([&, start, interval, i] {
            PrimeFinder::findPrimes(primeList, start + interval * i + 1,  start + interval+interval*i, list_lock);
        });

    };

    for (auto& t : threadList) {
        t.join();
    }

    sort(primeList.begin(), primeList.end());
    for (int i : primeList){
        cout << i << endl;
    };
    return 0;
}


