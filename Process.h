//
// Created by Pulkit Arora on 18/06/17.
//

#ifndef MEMORYMANAGER_PROCESS_H
#define MEMORYMANAGER_PROCESS_H

#include <string>
#include "MemorySlab.h"

/**
 * This is the class declaration for a Process.
 * Process always has a pid(process id) and the pointer to the memory to be written to.
 * A process cannot be instantiated without a pid.
 */

class Process {
    unsigned int pid;

    MemorySlab *currentUnused = nullptr;

    void setPid(unsigned int pid);

    MemorySlab *getCurrentUnused() const;

    void setCurrentUnused(MemorySlab *currentUnused);

    void updateUnusedMemory(MemorySlab *slab);

    void freeMemory();

    friend class MemoryManager;

public:

    unsigned int getPid() const;

    Process(int pid);

    void write(std::string s);
};


#endif //MEMORYMANAGER_PROCESS_H
