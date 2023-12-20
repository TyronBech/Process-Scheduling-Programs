#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<utility>
#include<algorithm>

struct Process{
    unsigned at;
    unsigned bt;
    unsigned pr;
};

int main(){
    std::vector<Process> processes;
    std::vector<std::pair<size_t, Process>> queue;
    std::vector<std::pair<size_t, unsigned>> completion;
    std::vector<std::pair<unsigned, unsigned>> TTWT;
    return 0;
}