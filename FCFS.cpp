#include<iostream>
#include<vector>
#include<sstream>
#include<string>
#include<utility>

int main(){
    std::vector<std::pair<size_t, unsigned>> processes;
    std::vector<unsigned> completion;
    std::vector<std::pair<unsigned, unsigned>> TTWT;
    unsigned sum = 0, TT = 0;
    std::string arrival_t = "", burst_t = "";
    unsigned rt_num, bt_num;
    std::cout << "Process Scheduling (FCFS)" << std::endl;
    std::cout << "Enter the arrival time: ";
    std::getline(std::cin >> std::ws, arrival_t);
    std::cout << "Enter the burst time: ";
    std::getline(std::cin >> std::ws, burst_t);
    std::stringstream rtss(arrival_t);
    std::stringstream btss(burst_t);
    while(rtss >> rt_num && btss >> bt_num){
        processes.push_back(std::make_pair(rt_num, bt_num));
    }
    for(size_t i = 0; i < processes.size(); i++){
        sum += processes[i].second;
        completion.push_back(sum);
    }
    for(size_t i = 0; i < processes.size(); i++){
        TT = completion[i] - processes[i].first;
        TTWT.push_back(std::make_pair(TT, (TT - processes[i].second)));
    }
    std::cout << "ID\t\tAT\t\tBT\t\tCT\t\tTT\t\tWT" << std::endl;
    for(size_t i = 0; i < processes.size(); i++){
        std::cout << "J" << i + 1 << "\t\t" << processes[i].first << "\t\t" << processes[i].second <<
        "\t\t" << completion[i] << "\t\t" << TTWT[i].first << "\t\t" << TTWT[i].second << std::endl; 
    }
    return 0;
}