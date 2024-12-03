#include <bits/stdc++.h>

#include "include/IOModule.hpp"
#include "include/memoryManager.hpp"
#include "include/task.hpp"

using namespace std;

IOModule::IOModule(int implementation)
{
    this->implementation = implementation;

    // initialize the memory manager
    MemoryManager memoryManager;
    
    // read the trace file
    cout << "Reading trace file..." << endl;
    ifstream traceFile("trace.txt");
    string trace;
    while (getline(traceFile, trace))
    {
        AllocateMemoryToTask(trace);
    }
}

void IOModule::AllocateMemoryToTask(string trace)
{
    // split the trace into task ID, Logical address and size
    vector<string> tokens = split(trace, ':');

    // convert taskID string(T1, T2, etc.) to int(1, 2, etc.)
    int taskID = stoi(tokens[0].substr(1));

    string logicalAddress = tokens[1];
    long long size = convertMemoryToBytes(tokens[2]);

    // check if the task already exists
    // iterate through the tasks vectors to find the task with the given taskID

    if(implementation == 0)
    {
        // page table as a map
        for (int i = 0; i < tasksMap.size(); i++)
        {
            if (tasksMap[i].getTaskID() == taskID)
            {
                // allocate memory to the task
                tasksMap[i].allocateMemory(logicalAddress, size);
                taskMemoryAllocated[taskID] += size;
                return;
            }
        }
    }
    else if (implementation == 1)
    {
        // single level page table
        for (int i = 0; i < tasksSingleLevel.size(); i++)
        {
            if (tasksSingleLevel[i].getTaskID() == taskID)
            {
                // allocate memory to the task
                tasksSingleLevel[i].allocateMemory(logicalAddress, size);
                taskMemoryAllocated[taskID] += size;
                return;
            }
        }
    }
    else
    {
        // two level page table
        for (int i = 0; i < tasksTwoLevel.size(); i++)
        {
            if (tasksTwoLevel[i].getTaskID() == taskID)
            {
                // allocate memory to the task
                tasksTwoLevel[i].allocateMemory(logicalAddress, size);
                taskMemoryAllocated[taskID] += size;
                return;
            }
        }
    }
    
    // else, create a new task object
    // if implementation is 0, create a TaskMap object
    if(implementation == 0)
    {
        TaskMap task(taskID, memoryManager);
        
        // allocate memory to the task
        task.allocateMemory(logicalAddress, size);
        taskMemoryAllocated[taskID] = size;

        tasksMap.push_back(task);
    }
    // if implementation is 1, create a TaskSingleLevel object
    else if(implementation == 1)
    {
        TaskSingleLevel task(taskID, memoryManager);

        // allocate memory to the task
        task.allocateMemory(logicalAddress, size);
        taskMemoryAllocated[taskID] = size;

        tasksSingleLevel.push_back(task);
    }
    // if implementation is 2, create a TaskTwoLevel object
    else
    {
        TaskTwoLevel task(taskID, memoryManager);

        // allocate memory to the task
        task.allocateMemory(logicalAddress, size);
        taskMemoryAllocated[taskID] = size;

        tasksTwoLevel.push_back(task);
    }
}


map<int, int> IOModule::getTaskPageHits()
{
    map<int, int> taskPageHits;
    
    for (int i = 0; i < tasksMap.size(); i++)
    {
        taskPageHits[tasksMap[i].getTaskID()] = tasksMap[i].getPageTableHits();
    }
    
    for (int i = 0; i < tasksSingleLevel.size(); i++)
    {
        taskPageHits[tasksSingleLevel[i].getTaskID()] = tasksSingleLevel[i].getPageTableHits();
    }
    
    for (int i = 0; i < tasksTwoLevel.size(); i++)
    {
        taskPageHits[tasksTwoLevel[i].getTaskID()] = tasksTwoLevel[i].getPageTableHits();
    }
    return taskPageHits;
}

map<int, int> IOModule::getTaskPageMisses()
{
    map<int, int> taskPageMisses;
    
    for (int i = 0; i < tasksMap.size(); i++)
    {
        taskPageMisses[tasksMap[i].getTaskID()] = tasksMap[i].getPageTableMisses();
    }
    
    for (int i = 0; i < tasksSingleLevel.size(); i++)
    {
        taskPageMisses[tasksSingleLevel[i].getTaskID()] = tasksSingleLevel[i].getPageTableMisses();
    }
    
    for (int i = 0; i < tasksTwoLevel.size(); i++)
    {
        taskPageMisses[tasksTwoLevel[i].getTaskID()] = tasksTwoLevel[i].getPageTableMisses();
    }
    return taskPageMisses;
}

map<int, int> IOModule::getTaskMemoryAllocated()
{
    return taskMemoryAllocated;
}

long long IOModule::getFreePhysicalMemory()
{
    return memoryManager.getFreePhysicalMemory();
}

// function that separates a string based on a delimiter
vector<string> IOModule::split(string trace, char delimiter)
{
    vector<string> tokens;
    string token;
    istringstream tokenStream(trace);
    while (getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

long long IOModule::convertMemoryToBytes(const string &memoryStr) 
{
    long long multiplier = 1;
    string numberPart = memoryStr.substr(0, memoryStr.size() - 2);
    string unitPart = memoryStr.substr(memoryStr.size() - 2);

    // convert the numeric part to a long long
    long long number = stoll(numberPart);

    // determine the multiplier based on the unit
    if (unitPart == "KB")
    {
        multiplier = 1024LL;
    } 
    else if (unitPart == "MB")
    {
        multiplier = 1024LL * 1024;
    }

    return number * multiplier;
}