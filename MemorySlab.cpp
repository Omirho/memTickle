//
// Created by Pulkit Arora on 18/06/17.
//

/**
 * Getters and Setters for MemorySlab class
 */

#include "MemorySlab.h"

char MemorySlab::getC() const {
    return c;
}

void MemorySlab::setC(char c) {
    MemorySlab::c = c;
}

MemorySlab *MemorySlab::getNext() const {
    return next;
}

void MemorySlab::setNext(MemorySlab *next) {
    MemorySlab::next = next;
}
