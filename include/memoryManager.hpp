#ifndef MEMORY_MANAGER_HPP
#define MEMORY_MANAGER_HPP

#include <iostream>
#include <vector>
#include "config.h"

using namespace std;

class MemoryManager {
public:
    MemoryManager();  // Constructor declaration

    vector<int> allocatePages(int numberOfPages);  // Allocate pages and return their indexes
    long long getFreePhysicalMemory();  // Get the amount of free physical memory

private:
    int* physicalPages;  // Physical page table to track memory allocation
};

#endif // MEMORY_MANAGER_HPP
