// Quicksort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include <vector>

void QuickSort(std::vector<int>* numbers, int &mem_access, int &num_comp);
void QuickSortRecurse(std::vector<int>* numbers, int i, int k, int &mem_access, int &num_comp);
int Partition(std::vector<int>* numbers, int i, int k, int &mem_access, int &num_comp);