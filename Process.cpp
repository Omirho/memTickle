//
// Created by Pulkit Arora on 18/06/17.
//

#include "Process.h"

/**
 * Default constructor override
 * @param pid
 */
Process::Process(int pid) {
    if (pid <= 0) {
        throw std::invalid_argument("PID should be a positive integer");
    }
    setPid(pid);
}

/**
 * Write the string s to the memory allocated to the memory,
 * which has not previously been written to.
 * @param s
 */
void Process::write(std::string s) {
    MemorySlab *start = getCurrentUnused();
    bool valid = true;
    for (int i=0; i<s.length(); i++) {
        if (start == nullptr) {
            valid = false;
            break;
        }
        start->setC(s[i]);
        start = start->getNext();
    }
    if (valid) {
        setCurrentUnused(start);
    } else {
        throw std::invalid_argument("String is longer than available memory");
    }
}

/**
 * Updates the current unused pointer if it is null and some memory
 * has been alloted to the process
 * @param slab
 */
void Process::updateUnusedMemory(MemorySlab *slab) {
    if (getCurrentUnused() == nullptr) {
        setCurrentUnused(slab);
    }
}

/**
 * Sets the current unused pointer to null when the memory
 * has been freed
 */
void Process::freeMemory() {
    setCurrentUnused(nullptr);
}

/**
 * Getters and setters for Process class
 */
unsigned int Process::getPid() const {
    return pid;
}

void Process::setPid(unsigned int pid) {
    Process::pid = pid;
}

MemorySlab *Process::getCurrentUnused() const {
    return currentUnused;
}

void Process::setCurrentUnused(MemorySlab *currentUnused) {
    Process::currentUnused = currentUnused;
}
