//
// Created by Leon Hesthaug on 06/04/2023.
//

#ifndef OVING2_CPP_WORKERS_H
#define OVING2_CPP_WORKERS_H

#include <thread>
#include <vector>
#include <queue>


using namespace std;
class Workers {
    int numWorkers;
    mutex lock;
    condition_variable cv;
    bool busy = false;
    bool stop = false;
    vector<thread> threads;
    queue<function<void()>> functions;

public:
    explicit Workers(int numWorkers);
    void run();
    void start();
    void post(const ::function<void()>& func);
    void joinThreads();

};


#endif //OVING2_CPP_WORKERS_H
