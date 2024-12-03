#include "memoryManager.hpp"
#include "task.hpp"
#include <bits/stdc++.h>

using namespace std;

class IOModule
{
    public:
        IOModule(int implementation);
        map<int, int> getTaskMemoryAllocated();
        long long getFreePhysicalMemory();
        map<int, int> getTaskPageHits();
        map<int, int> getTaskPageMisses();
    private:
        void AllocateMemoryToTask(string trace);
        vector<string> split(string trace, char delimiter);
        long long convertMemoryToBytes(const string &memoryStr);

        MemoryManager memoryManager;
        
        vector<TaskMap> tasksMap;
        vector<TaskSingleLevel> tasksSingleLevel;
        vector<TaskTwoLevel> tasksTwoLevel;

        map<int, int> taskMemoryAllocated;

        int implementation;
};
