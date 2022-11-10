#include <iostream>
#include <fstream>
#include "json.hpp"

using namespace std;
//g++ -Wall -Werror -std=c++11 sortedverification.cxx -o sorted
//./sorted SampleExample.json


int main(int argc, char** argv) {

    ifstream file;
    file.open(argv[1]);
    nlohmann::json data;
    nlohmann::json output; //output json
    if (file.is_open()) {
        data = nlohmann::json::parse(file);
    }
    
    //cout << data.dump(2) << endl;
    
    bool samplesWithInversions_bool = false;
    int samplesWithInversions = 0;
    int num_samples;
    //checking if array is sorted in sample
    for (auto itr = data.begin(); itr != data.end(); ++itr) {  

        if (itr.key() != "metadata") { //skipping over metadata
            num_samples += 1;
            vector<int> sample = itr.value();
            samplesWithInversions = 0;


            for (long unsigned int i = 0; i < sample.size()-1; i++) { // iterate over the sample
                if (sample[i] >= sample[i+1]) { // if there is a consecutive inversion
                    samplesWithInversions_bool = true;
                    output[itr.key()]["ConsecutiveInversions"][to_string(i)] = {sample[i], sample[i+1]};
                    output[itr.key()]["sample"] = data[itr.key()];
                }
            }
            
            if (samplesWithInversions_bool == true) {
                samplesWithInversions += 1;
            }
        }

    }
        
    
    output["metadata"]["arraySize"] = data["metadata"]["arraySize"];
    string filename = argv[1];
    output["metadata"]["file"] = filename;
    output["metadata"]["numSamples"] = data["metadata"]["numSamples"];
    output["metadata"]["samplesWithInversions"] = samplesWithInversions;

    cout << output.dump(2) << endl;
    
        
    return 1;
}