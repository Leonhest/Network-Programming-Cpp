//
// Created by Leon Hesthaug on 04/04/2023.
//

#ifndef OVING1_CPP_PRIMEFINDER_H
#define OVING1_CPP_PRIMEFINDER_H

#include <vector>
#include <mutex>

using namespace std;
class PrimeFinder {

public:
    static void findPrimes(vector<int> &primeList, int start, int end, mutex &list_lock);
};


#endif //OVING1_CPP_PRIMEFINDER_H
