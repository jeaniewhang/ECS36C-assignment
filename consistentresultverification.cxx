#include <iostream>
#include <fstream>
#include "json.hpp"


using namespace std;
 
int main(int argc, char** argv) {
    ifstream file1;
    ifstream file2;
    
    nlohmann::json jsonObject1;
    nlohmann::json jsonObject2;
    nlohmann::json output; //output json


    //cout << "json object 1";
    file1.open(argv[1]);
    if (file1.is_open()) {
        jsonObject1 = nlohmann::json::parse(file1);
    }

    //cout << "json object 2";
    file2.open(argv[2]);
    if (file2.is_open()) {
        jsonObject2 = nlohmann::json::parse(file2);
    }

    vector<int> sample1;
    vector<int> sample2;

    //string filename1 = argv[1];
    //string filename2 = argv[2];

    bool sampleWithConflict = false;
    int count;

    for (auto itr = jsonObject1.begin(); itr != jsonObject1.end(); ++itr) {  
        if (itr.key() != "metadata") {

            sample1.clear();
            sample2.clear();
            count = 0;
            
            for (auto arrayItr = jsonObject1[itr.key()].begin(); arrayItr != jsonObject1[itr.key()].end(); ++arrayItr) {  
                sample1.push_back(*arrayItr);
                
            }

            for (auto arrayItr = jsonObject2[itr.key()].begin(); arrayItr != jsonObject2[itr.key()].end(); ++arrayItr) {  
                sample2.push_back(*arrayItr);
            }   
            
            for (long unsigned int i = 0; i < sample1.size(); i++) {
                if (sample1[i] != sample2[i]) {
                    sampleWithConflict = true;
                    output[itr.key()][argv[2]] = jsonObject2[itr.key()];
                    output[itr.key()]["Mismatches"][to_string(i)] = {sample1[i], sample2[i]};
                    output[itr.key()][argv[1]] = jsonObject1[itr.key()];
                    
                }
            }
            
            if (sampleWithConflict == true) {
                count += 1;
            }
        }
    }


    string filename1 = argv[1];

    output["metadata"]["File1"]["arraySize"] = jsonObject1["metadata"]["arraySize"];
    output["metadata"]["File1"]["name"] = filename1;
    output["metadata"]["File1"]["numSamples"] = jsonObject1["metadata"]["numSamples"];
    
    string filename2 = argv[2];

    output["metadata"]["File2"]["arraySize"] = jsonObject2["metadata"]["arraySize"];
    output["metadata"]["File2"]["name"] = filename2;
    output["metadata"]["File2"]["numSamples"] = jsonObject2["metadata"]["numSamples"];

    output["metadata"]["samplesWithConflictingResults"] = count;

    cout << output.dump(2) << endl;

    
    return 1;
}