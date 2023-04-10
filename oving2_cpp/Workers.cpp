//
// Created by Leon Hesthaug on 06/04/2023.
//

#include <thread>
#include <iostream>
#include "Workers.h"

Workers::Workers(int numWorkers) : numWorkers(numWorkers) {
}

void Workers::start() {
    for(int i = 0; i < numWorkers; i++){
        threads.emplace_back([&,this] {
            run();
        });

    }
}

void Workers::run() {
   while (!stop){
       unique_lock lk(lock);
       cv.wait(lk, [this]{return !busy;});
       cv.wait(lk, [this] {return !functions.empty() || stop;});
        if (stop){
           cv.notify_all();
           busy = false;
           lk.unlock();
           break;
        }

        busy = true;
        function func = functions.front();
        functions.pop();

        cv.notify_all();
        busy = false;
        lk.unlock();

        func.operator()();

        if (stop) break;
    }


}

void Workers::post(const ::function<void()>& func) {

    unique_lock lk(lock);
    cv.wait(lk, [this] {return !busy;});
    busy = true;
    functions.push(func);
    cv.notify_all();
    busy = false;
    lk.unlock();
}

void Workers::joinThreads() {
    unique_lock lk(lock);
    cv.wait(lk, [this]{return functions.empty();});
    stop = true;
    cv.notify_all();
    lk.unlock();
    for (auto& i : threads){
        i.join();
    }
}


