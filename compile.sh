#!/bin/bash

# Clean up previous build
rm -f *.o app

# Compile source files
g++ -c memoryManager.cpp -o memoryManager.o
g++ -c task.cpp -o task.o
g++ -c IOModule.cpp -o IOModule.o
g++ -c performanceModule.cpp -o performanceModule.o
g++ -c testModule.cpp -o testModule.o

# Link object files into an executable
g++ testModule.o performanceModule.o IOModule.o task.o memoryManager.o -o app

# Clean up object files
rm -f *.o