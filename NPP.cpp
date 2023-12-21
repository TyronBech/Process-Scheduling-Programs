#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<utility>
#include<algorithm>

struct Process{
    int at = 0;
    int bt = 0;
    int pr = 0;
};

int main(){
    std::vector<Process> processes;
    std::vector<std::pair<size_t, unsigned>> completion;
    std::vector<std::pair<size_t, Process>> queue;
    std::vector<std::pair<unsigned, unsigned>> TTWT;
    std::string arrival_t = "", burst_t = "", priority = "";
    unsigned at_num, bt_num, pr_num, time_sum = 0;
    std::cout << "Enter arrival time: ";
    std::getline(std::cin >> std::ws, arrival_t);
    std::cout << "Enter burst time: ";
    std::getline(std::cin >> std::ws, burst_t);
    std::cout << "Enter priority number: ";
    std::getline(std::cin >> std::ws, priority);
    std::istringstream ss_at(arrival_t);
    std::istringstream ss_bt(burst_t);
    std::istringstream ss_pr(priority);
    while(ss_at >> at_num && ss_bt >> bt_num && ss_pr >> pr_num){
        Process p;
        p.at = at_num;
        p.bt = bt_num;
        p.pr = pr_num;
        processes.push_back(p);
        time_sum += bt_num; 
    }
    std::pair<size_t, Process> processing;
    unsigned i = 0;
    size_t j = 0;
    while(i < time_sum){
        while(i >= processes[j].at && j < processes.size()){
            queue.push_back(std::make_pair(j, processes[j]));
            j++;
        }
        if(!queue.empty()){
            std::sort(queue.begin(), queue.end(), [](const std::pair<size_t, Process>& a, const std::pair<size_t, Process>& b)
            { return (a.second.pr < b.second.pr)
            || (a.second.pr == b.second.pr && a.second.at < b.second.at)
            || (a.second.pr == b.second.pr && a.second.at == b.second.at && a.first < b.first); });
            processing = queue[0];
            while(processing.second.bt > 0){
                processing.second.bt--;
                i++;
            }
            completion.push_back(std::make_pair(processing.first, i));
            queue.erase(queue.begin());
        }
    }
    int TT;
    std::sort(completion.begin(), completion.end(), [](const std::pair<size_t, unsigned>& a, const std::pair<size_t, unsigned>& b)
    { return a.first < b.first; });
    for(size_t i = 0; i < processes.size(); i++){
        TT = completion[i].second - processes[i].at;
        TTWT.push_back(std::make_pair(TT, TT - processes[i].bt));
    }
    std::cout << "ID\t\tAT\t\tBT\t\tPR\t\tCT\t\tTT\t\tWT" << std::endl;
    for(size_t i = 0; i < processes.size(); i++){
        std::cout << "J" << i + 1 << "\t\t" << processes[i].at << "\t\t"
                << processes[i].bt << "\t\t" << processes[i].pr << "\t\t"
                << completion[i].second << "\t\t" << TTWT[i].first << "\t\t"
                << TTWT[i].second << std::endl;
    }
    return 0;
}