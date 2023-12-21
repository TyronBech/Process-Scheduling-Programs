#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<utility>
#include<algorithm>
// Checked
struct Process{
    unsigned at = 0;
    unsigned bt = 0;
};

int main(){
    std::vector<Process> processes;
    std::vector<std::pair<size_t, Process>> queue;
    std::vector<std::pair<size_t, unsigned>> completion;
    std::vector<std::pair<unsigned, unsigned>> TTWT;
    std::string arrival_t = "", burst_t = "";
    unsigned quantum, at_num, bt_num, time_sum = 0, TT;
    std::cout << "Enter arrival time: ";
    std::getline(std::cin >> std::ws, arrival_t);
    std::cout << "Enter burst time: ";
    std::getline(std::cin >> std::ws, burst_t);
    std::cout << "Enter quantum time: ";
    std::cin >> quantum;
    std::istringstream ss_at(arrival_t);
    std::istringstream ss_bt(burst_t);
    while(ss_at >> at_num && ss_bt >> bt_num){
        Process p;
        p.at = at_num;
        p.bt = bt_num;
        processes.push_back(p);
        time_sum += bt_num;
    }
    size_t j = 0;
    unsigned start = 0;
    for(unsigned time = 0; time < time_sum; ++time){
        while(time == processes[j].at){
            queue.push_back(std::make_pair(j, processes[j]));
            j++;
        }
        if(start >= quantum && !queue.empty()){
            queue.push_back(queue[0]);
            queue.erase(queue.begin());
            start = 0;
        }
        if(!queue.empty()){
            queue[0].second.bt--;
            start++;
            if(queue[0].second.bt == 0){
                completion.push_back(std::make_pair(queue[0].first, time + 1));
                queue.erase(queue.begin());
                start = 0;
            }
        }
    }
    std::sort(completion.begin(), completion.end(), [](const std::pair<size_t, unsigned>& a, const std::pair<size_t, unsigned>& b)
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