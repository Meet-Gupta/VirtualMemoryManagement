#ifndef TASK_HPP
#define TASK_HPP

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "memoryManager.hpp"
#include "config.h"

using namespace std;

class TaskMap
{
public:
    TaskMap(int taskID, MemoryManager memoryManager);            // Constructor declaration
    void allocateMemory(string logicalAddress, long long size);  // Allocate memory for the task
    int getTaskID();  // Get the task ID
    int getPageTableHits();
    int getPageTableMisses();

private:
    int taskID;  // Task ID
    MemoryManager memoryManager;  // Memory Manager object

    map<int, int> pageTable;  // Page table for the task
    int* pageTable1;  // Page table for the task


    int pageTableHits;
    int pageTableMisses;

};

class TaskSingleLevel
{
public:
    TaskSingleLevel(int taskID, MemoryManager memoryManager);  // Constructor declaration
    void allocateMemory(string logicalAddress, long long size);  // Allocate memory for the task
    int getTaskID();  // Get the task ID
    int getPageTableHits();
    int getPageTableMisses();

private:
    int taskID;  // Task ID
    MemoryManager memoryManager;  // Memory Manager object

    int* pageTable;  // Page table for the task
    int pageTableHits;
    int pageTableMisses;

};

class TaskTwoLevel
{
public:
    TaskTwoLevel(int taskID, MemoryManager memoryManager);  // Constructor declaration
    void allocateMemory(string logicalAddress, long long size);  // Allocate memory for the task
    int getTaskID();  // Get the task ID
    int getPageTableHits();
    int getPageTableMisses();

private:
    int taskID;  // Task ID
    MemoryManager memoryManager;  // Memory Manager object

    int pageTable[PAGE_TABLE_SIZE_1][PAGE_TABLE_SIZE_2];  // 2-level page table for the task
    int pageTableHits;
    int pageTableMisses;
};

#endif // TASK_HPP