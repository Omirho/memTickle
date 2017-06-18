//
// Created by Pulkit Arora on 18/06/17.
//

#include <iostream>
#include <cmath>
#include "MemoryManager.h"

/**
 * Default constructor override
 * @param blockSize
 */
MemoryManager::MemoryManager(int blockSize) {
    if (blockSize <= 0) {
        throw std::invalid_argument("Block size should be positive");
    }
    setBlockSize(blockSize);
}

/**
 * Allocate memory to the process p of size size.
 *
 * @param p
 * @param size
 * @return True if allocation succeeded, false otherwise
 */
bool MemoryManager::allocate(Process &p, int size) {
    if (size < 0) {
        throw std::invalid_argument("Negative memory cannot be allotted.");
    }
    if (size == 0) {
        // No need to allocate any memory
        return true;
    }

    // Allocate the desired memory and remove from free memory
    MemorySlab *endPosition = findEndPosition(size);
    if (endPosition == nullptr) {
        return false;
    }
    MemorySlab *startPosition(getFreeMemory());

    // Change the pointer to the free memory
    setFreeMemory(endPosition->getNext());

    // Change last memory slab to point to null
    endPosition->setNext(nullptr);

    // Add memory to the map
    addToUsedMemory(p, startPosition);

    // Update the current pointer in the process
    p.updateUnusedMemory(startPosition);
    return true;
}

/**
 * Free the memory belonging to the process p
 * and add it to free memory.
 * @param p
 */
void MemoryManager::free(Process &p) {
    MemorySlab *temp, *current = getProcessMemory(p);
    // Iterate over the memory slabs allocated to the process and
    // add them to the free memory.
    while (current != nullptr) {
        temp = current->getNext();
        addSlabToFreeMemory(current);
        current = temp;
    }

    // Reassign the current pointer in the process
    p.freeMemory();

    // Remove process from the map
    processToMemory.erase(p.getPid());
}

/**
 * Print the data in the memory belonging to the process
 * Considering it the memory footprint
 * @param p
 */
void MemoryManager::showMemoryFootprint(Process &p) {
    if (processToMemory.find(p.getPid()) != processToMemory.end()) {
        // Iterate over the memory slabs and print the characters stored in them
        // Some might contain garbage values
        MemorySlab *current = getProcessMemory(p);
        while (current != nullptr) {
            std::cout << current->getC();
            current = current->getNext();
        }
        std::cout << std::endl;
    }
}

/**
 * Find the end position in the free memory for the size given
 * Requests for more memory and adds it to free memory if required
 * @param size
 * @return Pointer to memory slab for the end position, null if allocation fails
 */
MemorySlab *MemoryManager::findEndPosition(size_t size) {
    if (getFreeMemory() == nullptr) {
        // If no free memory available, allocate required memory
        // from system
        MemorySlab *slab = requestMemoryBlocksFromSystem(getRequiredBlocks(size));
        if (slab == nullptr) {
            return nullptr;
        }
        setFreeMemory(slab);
    }

    // Try to allocate required slabs from free memory
    MemorySlab *endPosition(getFreeMemory());
    while (endPosition->getNext() != nullptr and size > 1) {
        endPosition = endPosition->getNext();
        size--;
    }

    // If free memory is not sufficient, request more memory from system
    if (size > 1) {
        MemorySlab *slab = requestMemoryBlocksFromSystem(getRequiredBlocks(size));
        if (slab == nullptr) {
            return nullptr;
        }
        endPosition->setNext(slab);
    }

    // Allocate the remaining memory for the process
    while (endPosition->getNext() != nullptr and size > 1) {
        endPosition = endPosition->getNext();
        size--;
    }

    // Return the pointer to the last slab allocated
    return endPosition;
}

/**
 * Add the memory slab to the process memory.
 * @param p
 * @param slab
 */
void MemoryManager::addToUsedMemory(Process &p, MemorySlab *slab) {
    MemorySlab *current = getProcessMemory(p);
    if (current != nullptr) {
        // Iterate to the end of the memory list and
        // append the given memory slab
        while (current->getNext() != nullptr) {
            current = current->getNext();
        }
        current->setNext(slab);
    } else {
        setProcessMemory(p, slab);
    }
}

/**
 * Add a memory slab to the free memory, keeping the sorted
 * order intact, i.e defragmented memory.
 * @param slab
 */
void MemoryManager::addSlabToFreeMemory(MemorySlab *slab) {
    if (getFreeMemory() != nullptr) {
        // Iterate over the free memory blocks to find
        // the correct position for the given slab
        MemorySlab *current = getFreeMemory();
        while (current != nullptr) {
            MemorySlab *next = current->getNext();
            if (current < slab and ((next == nullptr) or (next > slab))) {
                // Insert the memory slab in between current and next
                current->setNext(slab);
                slab->setNext(next);
                break;
            }
            current = current->getNext();
        }
    } else {
        setFreeMemory(slab);
    }
}

/**
 * Request the number of blocks from system.
 * @param numberOfBlocks
 * @return null is allocation failed, memory pointer otherwise
 */
MemorySlab *MemoryManager::requestMemoryBlocksFromSystem(size_t numberOfBlocks) {
    // Calculate the number of slabs to allocate from system
    // And call malloc
    size_t numberOfSlabs = numberOfBlocks * getBlockSize();
    MemorySlab *start = (MemorySlab *) malloc(numberOfSlabs * sizeof(MemorySlab));

    // Check if malloc failed
    if (start == nullptr) {
        return nullptr;
    }

    // Initialize the memory slabs to point to each other
    MemorySlab *current = start;
    while (--numberOfSlabs) {
        current->setNext(current + 1);
        current = current->getNext();
    }
    current->setNext(nullptr);

    // Return the pointer to the first memory block
    return start;
}

/**
 * Calculates the number of blocks to request from the system
 * @param size
 * @return Number of blocks
 */
size_t MemoryManager::getRequiredBlocks(size_t size) {
    return (size_t) ceil((double) size / getBlockSize());
}

/**
 * Getters and setters for the MemoryManager class.
 */

size_t MemoryManager::getBlockSize() const {
    return blockSize;
}

void MemoryManager::setBlockSize(size_t blockSize) {
    MemoryManager::blockSize = blockSize;
}

MemorySlab *MemoryManager::getFreeMemory() const {
    return freeMemory;
}

void MemoryManager::setFreeMemory(MemorySlab *freeMemory) {
    MemoryManager::freeMemory = freeMemory;
}

MemorySlab *MemoryManager::getProcessMemory(Process &p) {
    return processToMemory[p.getPid()];
}

void MemoryManager::setProcessMemory(Process &p, MemorySlab *slab) {
    MemoryManager::processToMemory[p.getPid()] = slab;
}
