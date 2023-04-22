#pragma once

#include "CodeHandler.h"


class ThreadManager
{
    ThreadManager() : thread(new std::thread)
    {}
    ~ThreadManager()
    {
        thread->join();
        delete thread;
    }
    std::thread *thread;
};