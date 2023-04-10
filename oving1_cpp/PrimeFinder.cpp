//
// Created by Leon Hesthaug on 04/04/2023.
//

#include <vector>
#include <iostream>
#include <cmath>
#include "PrimeFinder.h"

using namespace std;

void PrimeFinder::findPrimes(vector<int> &primeList, int start, int end, mutex &list_lock) {
    for (int i = start; i <= end; i++){
        if (i == 1) continue;
        bool prime = true;
        for (int j = 2; j <= sqrt(i); j++){
            if (i%j == 0){
                prime = false;
                break;
            }
        }
        if (prime) {
            list_lock.lock();
            primeList.push_back(i);
            list_lock.unlock();
        }
    }
}
