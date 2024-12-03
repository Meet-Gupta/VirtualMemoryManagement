#include <bits/stdc++.h>

#include "include/config.h"

using namespace std;

#include "include/memoryManager.hpp"

MemoryManager::MemoryManager()
{
    physicalPages = new int[PHYSICAL_PAGES];
}

vector<int> MemoryManager::allocatePages(int numberOfPages)
{
    vector<int> physicalPagesAllocated;

    // Calculate number of pages required using size
    // int numberOfPages = size / PAGE_SIZE;

    // Iterate through the physicalPages array to find the first element whose value is 0
    for (int i = 0; i < PHYSICAL_PAGES; i++) {
        // Allocate the first available page
        if (physicalPages[i] == 0) {
            // Set the page allocated to 1
            physicalPages[i] = 1;
            // Store the index of the page allocated
            physicalPagesAllocated.push_back(i+1);
        }

        // If all required pages are allocated, break
        if (physicalPagesAllocated.size() == numberOfPages)
        {
            break;
        }
    }

    // If no page is available, return error
    if (physicalPagesAllocated.size() < numberOfPages)
    {
        cout << "Not enough physical memory available" << endl;
    }

    // Return the indexes of the physical pages allocated
    return physicalPagesAllocated;
}

long long MemoryManager::getFreePhysicalMemory()
{
    long long freeMemory = 0;
    for (int i = 0; i < PHYSICAL_PAGES; i++) {
        if (physicalPages[i] == 0) {
            freeMemory += PAGE_SIZE;
        }
    }
    return freeMemory;
}