// Insertion Sort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks
#include <iostream>
#include "insertionsort.h"
#include <ctime>

void InsertionSort(std::vector<int>* numbers, int &mem_access, int &num_comp) {
   std::clock_t time1 = clock();
   int i = 0;
   int j = 0;
   
   int temp = 0;  // Temporary variable for swap
   
   for (i = 1; i < numbers->size(); ++i) {
      j = i;
      // Insert numbers[i] into sorted part
      // stopping once numbers[i] in correct position
      //num_comp++;
      //mem_access++;
      while (j > 0 && (*numbers)[j] < (*numbers)[j - 1]) {
         
         // Swap numbers[j] and numbers[j - 1]
         temp = (*numbers)[j];
         (*numbers)[j] = (*numbers)[j - 1];
         (*numbers)[j - 1] = temp;
         mem_access += 6;
         num_comp++;
         --j;
         
      }
      if (j > 0) {
            mem_access += 2;
            num_comp++;
      }
   }
   std::clock_t time2 = clock();
   time2 = time2 - time1;
   std::cout << time2 << ",";
   std::cout << num_comp << ",";
   std::cout << mem_access << ",";
   return;
   
   
}