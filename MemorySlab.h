//
// Created by Pulkit Arora on 18/06/17.
//

#ifndef MEMORYMANAGER_MEMORYSLAB_H
#define MEMORYMANAGER_MEMORYSLAB_H

/**
 * This is the class declaration for MemorySlab.
 * Memory slab holds data and a next slab pointer.
 * Data is only a character for proof of concept.
 */

class MemorySlab {
    char c;

    MemorySlab *next = nullptr;

public:

    char getC() const;

    void setC(char c);

    MemorySlab *getNext() const;

    void setNext(MemorySlab *next);
};


#endif //MEMORYMANAGER_MEMORYSLAB_H
