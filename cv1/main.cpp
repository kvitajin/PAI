#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <cmath>


std::vector<std::vector<int>> neigbours={
        { 0, 10, 15, 20 , 50, 70, 44},
        { 10, 0, 35, 25 , 77, 21, 63},
        { 15, 35, 0, 30 , 11, 69, 42},
        { 20, 25, 30, 0 , 31, 94, 28},
        { 50, 77, 11, 31,  0, 72, 14},
        { 70, 21, 69, 94, 72,  0, 19},
        { 44, 63, 42, 28, 14, 19,  0},
};
//std::vector<std::vector<int>> neigbours={
//        { 0, 10, 15, 20 },
//        { 10, 0, 35, 25 },
//        { 15, 35, 0, 30 },
//        { 20, 25, 30, 0 }
//};
std::vector<int> pokus ={0,1,2,3};

std::vector<int> results;

void TSP (){
    int tmp;
    do {
        tmp=0;
        for (int i = 0; i < neigbours.size()-1; ++i) {        //-1
            tmp+=neigbours[pokus[i]][pokus[i+1]];
        }
        std::cout   << (tmp)<<"\t";
    }
    while (std::next_permutation(pokus.begin(), pokus.end()));
}

void partialTSP(std::vector<int> permutations){
    int tmp;
    for (int i = 0; i <  std::tgamma(permutations.size()); ++i){
        tmp=0;
        for (int j = 0; j < neigbours.size()-1; ++j) {        //-1
            tmp+=neigbours[permutations[j]][permutations[j+1]];

        }
        results[i+std::tgamma(permutations.size())*permutations[0]]=tmp;
        std::next_permutation(permutations.begin(), permutations.end());
    }
}

std::vector<int> shift(std::vector<int> arr, int which){
    int tmp= arr[which];
    arr.erase(arr.begin()+which);
    arr.emplace(arr.begin(), tmp);

    return arr;
}

void PTSP(){
    std::vector<std::thread> threads;
    results.resize(tgamma((int)pokus.size()+1));
    for (int i = 0; i < pokus.size(); ++i) {
        threads.push_back(std::thread(partialTSP, shift(pokus, i)));

    }
    for (auto & thread : threads) {
        if (thread.joinable()){
            thread.join();
        }
    }

};

int main() {
    PTSP();
    for(auto  result : results )
        std::cout<<result<<std::endl;
    return 0;
}