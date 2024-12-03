    #include <bits/stdc++.h>
    #include <chrono>

    #include "include/IOModule.hpp"
    #include "include/performanceModule.hpp"
    #include "include/config.h"

    using namespace std;
    using namespace std::chrono;

    PerformanceModule::PerformanceModule() 
    {
        // Measure execution time for different implementations
        auto start = high_resolution_clock::now();
        IOModule ioModuleMap(0);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        executionTimes[0] = duration.count();

        start = high_resolution_clock::now();
        IOModule ioModuleSingleLevel(1);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        executionTimes[1] = duration.count();

        start = high_resolution_clock::now();
        IOModule ioModuleTwoLevel(2);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        executionTimes[2] = duration.count();

        // Report execution times and other details
        for (int i = 0; i < 3; i++) {
            if (i == 0)
            {
                cout << "Execution time for implementation : Map: " << executionTimes[i] << " microseconds" << endl;
                map<int, int> taskMemory = ioModuleMap.getTaskMemoryAllocated();
                cout << "Physical memory allocated to each task: " << endl;
                for (const auto& pair : taskMemory) {
                    cout << pair.first << ": " << pair.second << endl;
                }

                map<int, int> taskPageHits = ioModuleMap.getTaskPageHits();
                cout << "Page hits for each task: " << endl;
                for (const auto& pair : taskPageHits) {
                    cout << pair.first << ": " << pair.second << endl;
                }

                map<int, int> taskPageMisses = ioModuleMap.getTaskPageMisses();
                cout << "Page misses for each task: " << endl;
                for (const auto& pair : taskPageMisses) {
                    cout << pair.first << ": " << pair.second << endl;
                }
                cout << "Memory for Page Table: " <<  2 * VIRTUAL_PAGES * (BITS_VIRTUAL_SPACE / 8) << " Bytes" << endl;
                cout << "Free physical memory: " << ioModuleMap.getFreePhysicalMemory() << " Bytes" << endl;
            }
            else if (i == 1)
            {
                cout << "Execution time for implementation : Single-level: " << executionTimes[i] << " microseconds" << endl;
                map<int, int> taskMemory = ioModuleSingleLevel.getTaskMemoryAllocated();
                cout << "Physical memory allocated to each task: " << endl;
                for (const auto& pair : taskMemory) {
                    cout << pair.first << ": " << pair.second << endl;
                }
                
                map<int, int> taskPageHits = ioModuleSingleLevel.getTaskPageHits();
                cout << "Page hits for each task: " << endl;
                for (const auto& pair : taskPageHits) {
                    cout << pair.first << ": " << pair.second << endl;
                }

                map<int, int> taskPageMisses = ioModuleSingleLevel.getTaskPageMisses();
                cout << "Page misses for each task: " << endl;
                for (const auto& pair : taskPageMisses) {
                    cout << pair.first << ": " << pair.second << endl;
                }

                cout << "Memory for Page Table: " <<  VIRTUAL_PAGES * (BITS_VIRTUAL_SPACE / 8) << " Bytes" << endl;
                cout << "Free physical memory: " << ioModuleSingleLevel.getFreePhysicalMemory() << " Bytes" << endl;
            }
            else{
                cout << "Execution time for implementation : Two-level: " << executionTimes[i] << " microseconds" << endl;
                map<int, int> taskMemory = ioModuleTwoLevel.getTaskMemoryAllocated();
                cout << "Physical memory allocated to each task: " << endl;
                for (const auto& pair : taskMemory) {
                    cout << pair.first << ": " << pair.second << endl;
                }

                map<int, int> taskPageHits = ioModuleTwoLevel.getTaskPageHits();
                cout << "Page hits for each task: " << endl;
                for (const auto& pair : taskPageHits) {
                    cout << pair.first << ": " << pair.second << endl;
                }

                map<int, int> taskPageMisses = ioModuleTwoLevel.getTaskPageMisses();
                cout << "Page misses for each task: " << endl;
                for (const auto& pair : taskPageMisses) {
                    cout << pair.first << ": " << pair.second << endl;
                }

                cout << "Memory for Page Table: " << PAGE_TABLE_SIZE_1 * (PTE_SIZE_1 / 8) + PAGE_TABLE_SIZE_2 * (PTE_SIZE_2 / 8) << " Bytes" << endl;
                cout << "Free physical memory: " << ioModuleTwoLevel.getFreePhysicalMemory() << " Bytes" << endl;
            }
        }
    }