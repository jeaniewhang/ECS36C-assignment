// Merge Sort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks
#include <ctime>
#include <iostream>
#include "mergesort.h"

void MergeSort(std::vector<int>* numbers, int &mem_access, int &num_comp) {
   std::clock_t time1 = clock();
   
   MergeSortRecurse(numbers, 0, numbers->size() - 1, mem_access, num_comp);
   std::clock_t time2 = clock();
   time2 = time2 - time1;
   std::cout << time2 << ",";
   std::cout << num_comp << ",";
   std::cout << mem_access << ",";
   
}


void MergeSortRecurse(std::vector<int>* numbers, int i, int k, int &mem_access, int &num_comp) {
   int j = 0;
   
   if (i < k) {
      j = (i + k) / 2;  // Find the midpoint in the partition
      
      // Recursively sort left and right partitions
      MergeSortRecurse(numbers, i, j, mem_access, num_comp);
      MergeSortRecurse(numbers, j + 1, k, mem_access, num_comp);
      
      // Merge left and right partition in sorted order
      Merge(numbers, i, j, k, mem_access, num_comp);
   }
}

void Merge(std::vector<int>* numbers, int i, int j, int k, int &mem_access, int &num_comp) {
   int mergedSize = k - i + 1;                // Size of merged partition
   int mergePos = 0;                          // Position to insert merged number
   int leftPos = 0;                           // Position of elements in left partition
   int rightPos = 0;                          // Position of elements in right partition
   std::vector<int> mergedNumbers;
   mergedNumbers.resize(mergedSize);          // Dynamically allocates temporary array
                                              // for merged numbers
   
   leftPos = i;                               // Initialize left partition position
   rightPos = j + 1;                          // Initialize right partition position
   
   
   // Add smallest element from left or right partition to merged numbers
   while (leftPos <= j && rightPos <= k) {
      if ((*numbers)[leftPos] < (*numbers)[rightPos]) {
         mergedNumbers[mergePos] = (*numbers)[leftPos];
         num_comp++;
         mem_access += 4;
         ++leftPos;
         
         
      }
      else {
         mergedNumbers[mergePos] = (*numbers)[rightPos];
         ++rightPos;
         mem_access += 4;
         num_comp++;
      }
      ++mergePos;
   }
   
   // If left partition is not empty, add remaining elements to merged numbers
   while (leftPos <= j) {
      mergedNumbers[mergePos] = (*numbers)[leftPos];
      ++leftPos;
      ++mergePos;
      mem_access += 2;
   }
   
   // If right partition is not empty, add remaining elements to merged numbers
   while (rightPos <= k) {
      mergedNumbers[mergePos] = (*numbers)[rightPos];
      ++rightPos;
      ++mergePos;
      mem_access += 2;
   }
   
   // Copy merge number back to numbers
   for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
      (*numbers)[i + mergePos] = mergedNumbers[mergePos];
      mem_access += 2;
   }
}