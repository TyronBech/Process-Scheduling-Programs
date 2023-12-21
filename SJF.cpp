#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <utility>
#include <algorithm>

int main() {
    std::vector<std::pair<unsigned, unsigned>> processes;
    std::vector<std::pair<size_t, unsigned>> completion;
    std::vector<std::pair<size_t, std::pair<unsigned, unsigned>>> queue;
    std::vector<std::pair<unsigned, unsigned>> TTWT;
    unsigned sum = 0, TT = 0;
    std::string arrival_t = "", burst_t = "";
    unsigned at_num, bt_num, time_sum = 0;
    std::cout << "Process Scheduling (SJF)" << std::endl;
    std::cout << "Enter the arrival time: ";
    std::getline(std::cin >> std::ws, arrival_t);
    std::cout << "Enter the burst time: ";
    std::getline(std::cin >> std::ws, burst_t);

    std::istringstream ss_at(arrival_t);
    std::istringstream ss_bt(burst_t);
    while (ss_at >> at_num && ss_bt >> bt_num) {
        processes.push_back(std::make_pair(at_num, bt_num));
        time_sum += bt_num;
    }
    std::pair<size_t, std::pair<unsigned, unsigned>> pro;
    unsigned i = 0;
    size_t j = 0;
    while(i < time_sum) {
        while(i >= processes[j].first && j < processes.size()){
            queue.push_back(std::make_pair(j, processes[j]));
            j++;
        }
        std::sort(queue.begin(), queue.end(),
        [](const std::pair<size_t, std::pair<unsigned, unsigned>>& a, const std::pair<size_t, std::pair<unsigned, unsigned>>& b)
        { return a.second.second < b.second.second; });
        pro = queue[0];
        while(pro.second.second > 0) {
            pro.second.second--;
            i++;
        }
        completion.push_back(std::make_pair(pro.first, i));
        queue.erase(queue.begin());
    }
    std::sort(completion.begin(), completion.end(),
    [](const std::pair<size_t, unsigned>& a, const std::pair<size_t, unsigned>& b)
    { return a.first < b.first; });
    for(size_t i = 0; i < processes.size(); i++){
        TT = completion[i].second - processes[i].first;
        TTWT.push_back(std::make_pair(TT, TT - processes[i].second));
    }
    std::cout << "ID\t\tAT\t\tBT\t\tCT\t\tTT\t\tWT" << std::endl;
    for (size_t i = 0; i < processes.size(); i++) {
        std::cout << "J" << i + 1 << "\t\t" << processes[i].first << "\t\t"
                  << processes[i].second << "\t\t" << completion[i].second << "\t\t"
                  << TTWT[i].first << "\t\t" << TTWT[i].second << std::endl;
    }
    return 0;
}
