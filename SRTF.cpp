#include<iostream>
#include<vector>
#include<sstream>
#include<utility>
#include<algorithm>

struct Process{
    int at;
    int bt;
};

int main(){
    std::vector<Process> processes;
    std::vector<std::pair<int, Process>> queue;
    std::vector<std::pair<int, int>> completion;
    std::vector<std::pair<int, int>> TTWT;
    std::string arrival_t = "", burst_t = "";
    unsigned at_num, bt_num, time_sum = 0, TT;
    std::cout << "Enter arrival time: ";
    getline(std::cin >> std::ws, arrival_t);
    std::cout << "Enter burst time: ";
    getline(std::cin >> std::ws, burst_t);
    std::istringstream atss(arrival_t);
    std::istringstream btss(burst_t);
    while(atss >> at_num && btss >> bt_num){
        Process p; 
        p.at = at_num;
        p.bt = bt_num;
        processes.push_back(p);
        time_sum += bt_num;
    }
    size_t j = 0;
    std::pair<int, Process> processing;
    for(size_t time = 0; time < time_sum; time++){
        if(time == processes[j].at){
            queue.push_back(std::make_pair(j, processes[j]));
            j++;
        }
        std::sort(queue.begin(), queue.end(), [](const std::pair<int, Process>& a, const std::pair<int, Process>& b)
        { return a.second.bt < b.second.bt; });
        processing = queue[0];
        processing.second.bt--;
        if(processing.second.bt == 0){
            completion.push_back(std::make_pair(processing.first, time + 1));
            queue.erase(queue.begin());
        } else {
            queue.erase(queue.begin());
            queue.push_back(processing);
        }
    }
    std::sort(completion.begin(), completion.end(), [](std::pair<int, int>& a, std::pair<int, int>& b)
    { return a.first < b.first; });
    for(size_t i = 0; i < processes.size(); i++){
        TT = completion[i].second - processes[i].at;
        TTWT.push_back(std::make_pair(TT, TT - processes[i].bt));
    }
    std::cout << "ID\t\tAT\t\tBT\t\tCT\t\tTT\t\tWT" << std::endl;
    for (size_t i = 0; i < processes.size(); i++) {
        std::cout << "J" << i + 1 << "\t\t" << processes[i].at << "\t\t"
                  << processes[i].bt << "\t\t" << completion[i].second << "\t\t"
                  << TTWT[i].first << "\t\t" << TTWT[i].second << std::endl;
    }
    return 0;
}