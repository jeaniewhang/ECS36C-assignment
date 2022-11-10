#include "insertionsort.h"
#include "mergesort.h"
#include "quicksort.h"
#include <iostream>
#include <fstream>
#include "json.hpp"
#include <ctime>


using namespace std;

int main(int argc, char** argv) {
    ifstream file;
    file.open(argv[1]);
    nlohmann::json data;
    nlohmann::json output; //output json

    if (file.is_open()) {
        data = nlohmann::json::parse(file);
        //cout << data;
    }

    int i_mem = 0;
    int i_comp = 0;
    int m_mem = 0;
    int m_comp = 0;
    int q_mem = 0;
    int q_comp = 0;

    
    vector<int> sample;
    std::cout << "Sample,InsertionSortTime,InsertionSortCompares,InsertionSortMemaccess,MergeSortTime,MergeSortCompares,MergeSortMemaccess,QuickSortTime,QuickSortCompares,QuickSortMemaccess" << std::endl; 
    for (auto itr = data.begin(); itr != data.end(); ++itr) {
        if (itr.key() != "metadata") {
            sample = data[itr.key()].get<vector<int>>();
            cout << itr.key() << ",";

            InsertionSort(&sample, i_mem, i_comp);
            sample.clear();
            sample = data[itr.key()].get<vector<int>>();
            MergeSort(&sample, m_mem, m_comp);
            sample.clear();
            sample = data[itr.key()].get<vector<int>>();
            QuickSort(&sample, q_mem, q_comp);

            i_mem = 0;
            i_comp = 0;
            m_mem = 0;
            m_comp = 0;
            q_mem = 0;
            q_comp = 0;
            sample.clear();
        }
    }   
    

    

}