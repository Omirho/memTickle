//
// Created by Pulkit Arora on 18/06/17.
//

#ifndef MEMORYMANAGER_MEMORYMANAGER_H
#define MEMORYMANAGER_MEMORYMANAGER_H


#include "MemorySlab.h"
#include "Process.h"
#include <map>

/**
 * This is the class declaration for MemoryManager.
 * It holds the blockSize, a pointer to the free memory and
 * process to memory map.
 * The class provides allocate, free, and showMemoryFootprint functions.
 * A MemoryManager cannot be instantiated without a blockSize.
 */

class MemoryManager {
    size_t blockSize;

    MemorySlab *freeMemory = nullptr;

    std::map<unsigned int, MemorySlab*> processToMemory;

    size_t getBlockSize() const;

    void setBlockSize(size_t blockSize);

    MemorySlab *getFreeMemory() const;

    void setFreeMemory(MemorySlab *freeMemory);

    MemorySlab *getProcessMemory(Process &p);

    void setProcessMemory(Process &p, MemorySlab* slab);

    void addSlabToFreeMemory(MemorySlab *slab);

    MemorySlab *requestMemoryBlocksFromSystem(size_t numberOfBlocks);

    void addToUsedMemory(Process &p, MemorySlab *slab);

    size_t getRequiredBlocks(size_t size);

    MemorySlab *findEndPosition(size_t size);

public:

    MemoryManager(int blockSize);

    bool allocate(Process &p, int size);

    void free(Process &p);

    void showMemoryFootprint(Process &p);
};


#endif //MEMORYMANAGER_MEMORYMANAGER_H
