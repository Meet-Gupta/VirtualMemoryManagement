#ifndef CONFIG_H
#define CONFIG_H
#include <stdio.h>
#include <bits/stdc++.h>
#include <cmath>

const size_t BITS_VIRTUAL_SPACE = 32;
const size_t BITS_PHYSICAL_SPACE = 32;
const size_t BITS_PAGE_SIZE = 12;
const size_t BITs_BLOCK_SIZE = 24;


const size_t PAGE_SIZE = (1ULL<<BITS_PAGE_SIZE);
const size_t VIRTUAL_MEMORY_SIZE = (1ULL<<BITS_VIRTUAL_SPACE);
const size_t PHYSICAL_MEMORY_SIZE = (1ULL<<BITS_PHYSICAL_SPACE);
const size_t BLOCK_SIZE = (1ULL<<BITs_BLOCK_SIZE);

// single level page table
const size_t BLOCK_PAGES = BLOCK_SIZE/PAGE_SIZE;
const size_t VIRTUAL_PAGES = VIRTUAL_MEMORY_SIZE/PAGE_SIZE;
const size_t PHYSICAL_PAGES = PHYSICAL_MEMORY_SIZE/PAGE_SIZE;


// multi level page table
const size_t PTS_1 = (int) floor((BITS_VIRTUAL_SPACE - BITS_PAGE_SIZE)/2);
const size_t PTS_2 = (int) ceil((BITS_VIRTUAL_SPACE - BITS_PAGE_SIZE)/2);
const size_t PAGE_TABLE_SIZE_1 = 1 << (int) floor((BITS_VIRTUAL_SPACE - BITS_PAGE_SIZE)/2);
const size_t PAGE_TABLE_SIZE_2 = 1 << (int) ceil((BITS_VIRTUAL_SPACE - BITS_PAGE_SIZE)/2);
const size_t PTE_SIZE_1 = BITS_PHYSICAL_SPACE;
const size_t PTE_SIZE_2 = BITS_VIRTUAL_SPACE;


// starting address of memory sections
const size_t Text = 0x01000000;
const size_t Data = 0x04000000;
const size_t Bss = 0x0A000000;
const size_t Heap = 0x5E000000;
const size_t Shared = 0x40000000;
const size_t Stack = 0xB0000000;

#endif