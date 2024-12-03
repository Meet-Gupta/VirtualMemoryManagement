#include <iostream>
#include <fstream>
#include <cstdlib>
#include <bits/stdc++.h>
// i want to use pthreads
#include <pthread.h>
#include <unistd.h>


#include "include/performanceModule.hpp"
#include "include/config.h"

using namespace std;

int getNumberOfTasks();
void *generateTraceFile(void *arg);
void genTraceFile(int numberOfTasks);
string intToBin(long long n);
string binToHex(string binary);

pthread_mutex_t fileMutex;
ofstream traceFile;


int main()
{
    int numberOfTasks = getNumberOfTasks();
    
    // generate trace file with the format taskID:logicalAddress:size
    // generateTraceFile(numberOfTasks);
    genTraceFile(numberOfTasks);
    cout << "Trace file generated successfully!" << endl;
    // initialize the performance module
    PerformanceModule performanceModule;

    return 0;
}

int getNumberOfTasks() 
{
    int numberOfTasks;
    cout << "Enter the number of tasks: ";
    cin >> numberOfTasks;
    return numberOfTasks;
}

void *generateTraceFile(void *arg)
{
    int taskID = (int)((size_t)arg);
    for(int i=0;i<200;i++){
        int minPageSize = PAGE_SIZE / (1LL<<10);
        // random size from 1 to 10 times minPageSize
        int size = (rand() % 10 + 1) * minPageSize;
        // generate random logical address from 0 to VIRTUAL_PAGES
        long long logicalAddress = rand() % (BLOCK_PAGES-size/minPageSize);
        // cout<<logicalAddress<<endl;
        // convert to binary
        string logicalAddressBinary = intToBin(logicalAddress);
        logicalAddressBinary = logicalAddressBinary.substr(BITS_PAGE_SIZE,32-BITS_PAGE_SIZE);
        // cout<<logicalAddressBinary<<endl;
        // add random bits for offset
        for (int i = 0; i < BITS_PAGE_SIZE; i++)
        {
            // generate a random number from either 0 or 1
            int randomNumber = rand() % 2;
            logicalAddressBinary = logicalAddressBinary + to_string(randomNumber);
        }
        // cout<<logicalAddressBinary<<endl;
        // convert to hexadecimal
        string logicalAddressHex = binToHex(logicalAddressBinary);
        // while(logicalAddressHex.length()<6){
        //     logicalAddressHex="0"+logicalAddressHex;
        // }
        // cout<<logicalAddressHex<<endl;
        int randblock=rand()%6;
        if(randblock==0){
            logicalAddressHex = "01" + logicalAddressHex.substr(2,6);
        }
        else if(randblock==1){
            logicalAddressHex = "04" + logicalAddressHex.substr(2,6);
        }
        else if(randblock==2){
            logicalAddressHex = "0A" + logicalAddressHex.substr(2,6);
        }
        else if(randblock==3){
            logicalAddressHex = "5E" + logicalAddressHex.substr(2,6);
        }
        else if(randblock==4){
            logicalAddressHex = "40" + logicalAddressHex.substr(2,6);
        }
        else if(randblock==5){
            logicalAddressHex = "B0" + logicalAddressHex.substr(2,6);
        }
        logicalAddressHex = "0x" + logicalAddressHex;
        
        pthread_mutex_lock(&fileMutex);
        traceFile << "T" << taskID << ":" << logicalAddressHex << ":" << size << "KB" << endl;
        pthread_mutex_unlock(&fileMutex);
    }
}

void genTraceFile(int numberOfTasks)
{
 
    // create threads for each task
    pthread_t threads[numberOfTasks];
    traceFile.open("trace.txt");

    pthread_mutex_init(&fileMutex, nullptr);
    for (int i = 0; i < numberOfTasks; i++)
    {
        // pass taskID as argument
        int x=i+1;
        pthread_create(&threads[i], nullptr, &generateTraceFile, (void *)x);
    }
    for(int i=0;i<numberOfTasks;i++){
        pthread_join(threads[i], nullptr);}
}

// function to convert integer to binary
string intToBin(long long n)
{
    return bitset<32>(n).to_string();
}

// function to convert binary to hexadecimal
string binToHex(string binary)
{
    // Pad the binary string to ensure its length is a multiple of 4
    int padding = (4 - binary.length() % 4) % 4;
    binary = string(padding, '0') + binary;

    string hex = "";
    for (int i = 0; i < binary.length(); i += 4)
    {
        string nibble = binary.substr(i, 4);
        if (nibble == "0000")
        {
            hex += "0";
        }
        else if (nibble == "0001")
        {
            hex += "1";
        }
        else if (nibble == "0010")
        {
            hex += "2";
        }
        else if (nibble == "0011")
        {
            hex += "3";
        }
        else if (nibble == "0100")
        {
            hex += "4";
        }
        else if (nibble == "0101")
        {
            hex += "5";
        }
        else if (nibble == "0110")
        {
            hex += "6";
        }
        else if (nibble == "0111")
        {
            hex += "7";
        }
        else if (nibble == "1000")
        {
            hex += "8";
        }
        else if (nibble == "1001")
        {
            hex += "9";
        }
        else if (nibble == "1010")
        {
            hex += "A";
        }
        else if (nibble == "1011")
        {
            hex += "B";
        }
        else if (nibble == "1100")
        {
            hex += "C";
        }
        else if (nibble == "1101")
        {
            hex += "D";
        }
        else if (nibble == "1110")
        {
            hex += "E";
        }
        else if (nibble == "1111")
        {
            hex += "F";
        }
    }
    return hex;
}