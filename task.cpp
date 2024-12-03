#include <bits/stdc++.h>
#include <sstream>
#include <bitset>

#include "include/memoryManager.hpp"
#include "include/config.h"

using namespace std;

string hexToBin(const string& s);
long trimBinaryToDecimal(string binary, int bits);

#include "include/task.hpp"

// TaskMap class implementation
TaskMap::TaskMap(int taskID, MemoryManager memoryManager)
{
    pageTableHits = 0;
    pageTableMisses = 0;
    pageTable1 = new int[VIRTUAL_PAGES];  // Page table for the task

    this->taskID = taskID;
    this->memoryManager = memoryManager;
}

int TaskMap::getPageTableHits()
{
    return pageTableHits;
}
int TaskMap::getPageTableMisses()
{
    return pageTableMisses;
}

void TaskMap::allocateMemory(string logicalAddress, long long size)
{
    int numberOfPages = size / PAGE_SIZE;
    int hits = 0;

    // convert the logical address to the virtual page number
    string binaryAddress = hexToBin(logicalAddress);
    long startingPageNumber = trimBinaryToDecimal(binaryAddress, BITS_PAGE_SIZE);

    // check if the page table has a physical page number for the virtual page number
    for (int i = 0; i < numberOfPages; i++)
    {
        // if the page is already in the page table, count as a page table hit
        if (pageTable[startingPageNumber + i] != 0)
        {
            hits++;
        }
    }
    pageTableHits += hits;
    // add the rest of the pages to page table misses
    pageTableMisses += numberOfPages - hits;

    vector<int> physicalPages = memoryManager.allocatePages(numberOfPages - hits);

    for (int i = 0; i < numberOfPages; i++)
    {
        if (pageTable[startingPageNumber + i] == 0)
        {
            pageTable[startingPageNumber + i] = physicalPages[0];

            pageTable1[startingPageNumber + i] = physicalPages[0];
            physicalPages.erase(physicalPages.begin());
        }
    }
}

int TaskMap::getTaskID() 
{
    return taskID;
}

TaskSingleLevel::TaskSingleLevel(int taskID, MemoryManager memoryManager)
{
    pageTableHits = 0;
    pageTableMisses = 0;
    pageTable = new int[VIRTUAL_PAGES];  // Page table for the task

    this->taskID = taskID;
    this->memoryManager = memoryManager;
}

int TaskSingleLevel::getPageTableHits()
{
    return pageTableHits;
}

int TaskSingleLevel::getPageTableMisses()
{
    return pageTableMisses;
}
void TaskSingleLevel::allocateMemory(string logicalAddress, long long size)
{
    int numberOfPages = size / PAGE_SIZE;
    int hits = 0;

    string binaryAddress = hexToBin(logicalAddress);
    long startingPageNumber = trimBinaryToDecimal(binaryAddress, BITS_PAGE_SIZE);
    
    // check if the page table has the physical page number for the virtual page number
    for (int i = 0; i < numberOfPages; i++)
    {
        // if the page is already in the page table, count as a page table hit
        if (pageTable[startingPageNumber + i] != 0)
        {
            hits++;
        }
    }
    pageTableHits += hits;
    // add the rest of the pages to page table misses
    pageTableMisses += numberOfPages - hits;

    // call memory manager to allocate pages equal to page misses this time
    vector<int> physicalPages = memoryManager.allocatePages(numberOfPages - hits);
    
    // store the physical page number in the page table
    for (int i = 0; i < numberOfPages; i++)
    {
        // store the physical page number in the page table of only the pages that were not already in the page table
        if (pageTable[startingPageNumber + i] == 0)
        {
            // allocate the first physical page number to the virtual page number and remove it from the list of physical pages
            pageTable[startingPageNumber + i] = physicalPages[0];
            physicalPages.erase(physicalPages.begin());
        }
    }
}

int TaskSingleLevel::getTaskID()
{
    return taskID;
}

// TaskTwoLevel class implementation
TaskTwoLevel::TaskTwoLevel(int taskID, MemoryManager memoryManager)
{
    pageTableHits = 0;
    pageTableMisses = 0;
    this->taskID = taskID;
    this->memoryManager = memoryManager;

    for (int i = 0; i < PAGE_TABLE_SIZE_1; i++)
    {
        for (int j = 0; j < PAGE_TABLE_SIZE_2; j++)
        {
            pageTable[i][j] = 0;
        }
    }
}

int TaskTwoLevel::getPageTableHits()
{
    return pageTableHits;
}

int TaskTwoLevel::getPageTableMisses()
{
    return pageTableMisses;
}
void TaskTwoLevel::allocateMemory(string logicalAddress, long long size)
{
    int numberOfPages = size / PAGE_SIZE;
    int hits = 0;

    // convert the logical address to the virtual page numbers of the two levels
    string binaryAddress = hexToBin(logicalAddress);
    binaryAddress = binaryAddress.substr(0, binaryAddress.size() - BITS_PAGE_SIZE);

    string s1 = binaryAddress.substr(0, PTS_1);
    string s2 = binaryAddress.substr(PTS_2);
    
    long startingPageNumber1 = trimBinaryToDecimal(s1, 0);
    long startingPageNumber2 = trimBinaryToDecimal(s2, 0);

    // check if the page table has the physical page number for the virtual page number
    for (int i = 0; i < numberOfPages; i++)
    {
        // if the page is already in the page table, count as a page table hit
        if (pageTable[startingPageNumber1][startingPageNumber2 + i] != 0)
        {
            hits++;
        }
    }

    pageTableHits += hits;
    // add the rest of the pages to page table misses
    pageTableMisses += numberOfPages - hits;

    // call memory manager to allocate pages equal to page misses this time
    vector<int> physicalPages = memoryManager.allocatePages(numberOfPages - hits);

    for (int i = 0; i < numberOfPages; i++)
    {
        if (pageTable[startingPageNumber1][startingPageNumber2 + i] == 0)
        {
            pageTable[startingPageNumber1][startingPageNumber2 + i] = physicalPages[0];
            physicalPages.erase(physicalPages.begin());
        }
    }
}

int TaskTwoLevel::getTaskID()
{
    return taskID;
}

string hexToBin(const string& s) 
{
    stringstream ss;
    ss << hex << s;
    unsigned n;
    ss >> n;
    bitset<32> bin(n);

    // Convert the resulting binary back to a string
    return bin.to_string();
}

long trimBinaryToDecimal(string binary, int bits)
{
    bitset<32> bin(binary);

    bin >>= bits;

    return bin.to_ulong();
}