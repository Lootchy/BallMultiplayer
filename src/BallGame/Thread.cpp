#include <iostream>      
#include <string>          
#include "Thread.h"


void Thread::newthread() {
    CreateThread(NULL, 0, &Runnable::run_thread, this, 0, NULL);
}

DWORD Thread::run() {
    while (true) {
        std::cout << message << std::endl;
    }
    return 0;
}
