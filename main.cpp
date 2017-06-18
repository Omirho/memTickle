#include <iostream>
#include "MemoryManager.h"

/**
 * 2 processes allocating and deallocation memory.
 */
void test1() {
    MemoryManager memoryManager(10);
    Process p1(1), p2(2);
    memoryManager.allocate(p1, 5);
    p1.write("abcde");
    memoryManager.allocate(p2, 5);
    p2.write("qwert");
    memoryManager.showMemoryFootprint(p1);
    memoryManager.showMemoryFootprint(p2);
    memoryManager.free(p1);
    memoryManager.free(p2);
}

/**
 * Process allocating memory multiple times
 */
void test2() {
    MemoryManager memoryManager(10);
    Process p1(1);
    memoryManager.allocate(p1, 5);
    p1.write("fghij");
    memoryManager.showMemoryFootprint(p1);
    memoryManager.allocate(p1, 5);
    p1.write("klmno");
    memoryManager.showMemoryFootprint(p1);
}

/**
 * Multiple allocations and multiple writes
 */
void test3() {
    MemoryManager memoryManager(10);
    Process p3(3);
    memoryManager.allocate(p3, 1);
    memoryManager.allocate(p3, 1);
    memoryManager.allocate(p3, 1);
    memoryManager.allocate(p3, 1);
    memoryManager.allocate(p3, 1);
    memoryManager.allocate(p3, 1);
    memoryManager.allocate(p3, 1);
    memoryManager.allocate(p3, 1);
    memoryManager.allocate(p3, 1);
    p3.write("pqrs");
    p3.write("abcde");
    memoryManager.showMemoryFootprint(p3);
}

/**
 * Allocation after freeing memory
 */
void test4() {
    MemoryManager memoryManager(10);
    Process p1(1);
    memoryManager.allocate(p1, 4);
    p1.write("test");
    memoryManager.showMemoryFootprint(p1);
    memoryManager.free(p1);
    memoryManager.allocate(p1, 4);
    p1.write("agai");
    memoryManager.showMemoryFootprint(p1);
    memoryManager.allocate(p1, 2);
    p1.write("n!");
    memoryManager.showMemoryFootprint(p1);
}

/**
 * Multiple writes without allocation
 */
void test5() {
    MemoryManager memoryManager(10);
    Process p1(1), p2(2), p3(3);
    memoryManager.allocate(p1, 5);
    p1.write("a");
    p1.write("b");
    p1.write("c");
    p1.write("d");
    p1.write("e");
    memoryManager.allocate(p1, 3);
    p1.write("e");
    p1.write("f");
    p1.write("g");
    memoryManager.showMemoryFootprint(p1);
    memoryManager.free(p1);
    memoryManager.showMemoryFootprint(p1);
}

int main() {
    try {
        test1();
        test2();
        test3();
        test4();
        test5();
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}