#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<utility>
#include<algorithm>

/*
    Process structure, this is where the attributes of each process is stored
    at = arrival time
    bt = burst time
    pr = priority
*/
struct Process{
    unsigned at = 0;
    unsigned bt = 0;
    unsigned pr = 0;
};
// Main function
int main(){
    // vector for process inputs will be push to the processes vector
    // processes will be the raw input data, nothing will be changed here once done inputting
    std::vector<Process> processes;
    // vector for the ready queue of each process, once the arrival time is met or
    // (time = at) the process will be pushed to the queue according to the Preemtive priority algorithm
    // it will store the original index of each process and their Process structure
    std::vector<std::pair<size_t, Process>> queue;
    // vector to get the completion time and original index of the process, it is pair since
    // the queue doesn't store the processes by their index
    std::vector<std::pair<size_t, unsigned>> completion;
    // vector to store the result of turnaround time and waiting time of every processes
    std::vector<std::pair<unsigned, unsigned>> TTWT;
    // input variables for arrival time and burst time, input should be separated by spaces
    // input will be manipulated by the stringstream
    std::string arrival_t = "", burst_t = "", priority = "";
    /*
        at_num = temporary variable to store each input for arrival time
        bt_num = temporary variable to store each input for burst time
        pr_num = temporary variable to store each input for priority
        time_sum = variable to compute the total burst time of all process,
        it will be used in the for loop once the algorithm is started
        TT = temporary variable to store the turnaround time of each processes
    */
    unsigned at_num, bt_num, pr_num, time_sum = 0, TT;
    // inputting of arrival time, burst time, and priority
    std::cout << "Process Scheduling (PP)" << std::endl;
    std::cout << "Enter arrival time: ";
    std::getline(std::cin >> std::ws, arrival_t);
    std::cout << "Enter burst time: ";
    std::getline(std::cin >> std::ws, burst_t);
    std::cout << "Enter priority: ";
    std::getline(std::cin >> std::ws, priority);
    // std::istringstream is used to separate a single input into multiple integers
    // it is used for inputs like arrival time, burst time, and priority
    std::istringstream ss_at(arrival_t);
    std::istringstream ss_bt(burst_t);
    std::istringstream ss_pr(priority);
    // while loop for separation of inputs and storing those values in the processes vector
    // alongside with summing up the burst time of each processes
    while(ss_at >> at_num && ss_bt >> bt_num && ss_pr >> pr_num){
        Process p;
        p.at = at_num;
        p.bt = bt_num;
        p.pr = pr_num;
        processes.push_back(p);
        time_sum += bt_num;
    }
    size_t j = 0; // j will be used to traverse the processes vector
    // processing is the variable used to decrementing the burst time and updating the
    // contents of the queue
    std::pair<size_t, Process> processing;
    // for loop for Preemtive Priority algorithm
    // it is based on time which means it starts by 0 seconds/milliseconds
    // up until the total burst time - 1
    for(unsigned time = 0; time < time_sum; time++){
        // while the arrival time is equal to the current time, it will be pushed to the queue
        // getting ready for processing
        while(time == processes[j].at){
            queue.push_back(std::make_pair(j, processes[j]));
            j++;
        }
        if(!queue.empty()){
            // Each loop the queue will be sorted according to their priority or arrival time or ID
            std::sort(queue.begin(), queue.end(), [](const std::pair<size_t, Process>& a, const std::pair<size_t, Process>& b)
            { return (a.second.pr < b.second.pr)
            || (a.second.pr == b.second.pr && a.second.at < b.second.at)
            || (a.second.pr == b.second.pr && a.second.at == b.second.at && a.first < b.first); });
            // then the first element on the queue will be stored in the processing variable then decrements it
            processing = queue[0];
            processing.second.bt--;
            // if the burst time reach 0 it means its done, then the current time will be pushed to the completion vector
            // then erasing the first element in the queue, else moving the first element of the queue to the back of the queue
            if(processing.second.bt == 0){
                completion.push_back(std::make_pair(processing.first, time + 1));
                queue.erase(queue.begin());
            } else {
                queue.erase(queue.begin());
                queue.push_back(processing);
            }
        } else {
            // Idle time, the excess time will be added to the total time to reach the end time of process
            time_sum++;
        }
    }
    // after completing the process of decrementation of burst time for each process,
    // the completion vector will be sorted based on the original index of each process ascendingly
    std::sort(completion.begin(), completion.end(), [](const std::pair<size_t, unsigned>& a, const std::pair<size_t, unsigned>& b)
    { return a.first < b.first; });
    // for loop to compute for the turnaround time and waiting time for each processes
    // then adding it in the TTWT vector
    for(size_t i = 0; i < processes.size(); i++){
        TT = completion[i].second - processes[i].at;
        TTWT.push_back(std::make_pair(TT, TT - processes[i].bt));
    }
    // Lastly, display all the contents of the process from the process ID to waiting time
    std::cout << "ID\t\tAT\t\tBT\t\tPR\t\tCT\t\tTT\t\tWT" << std::endl;
    for(size_t i = 0; i < processes.size(); i++){
        std::cout << "J" << i + 1 << "\t\t" << processes[i].at << "\t\t"
                << processes[i].bt << "\t\t" << processes[i].pr << "\t\t"
                << completion[i].second << "\t\t" << TTWT[i].first << "\t\t"
                << TTWT[i].second << std::endl;
    }
    return 0;
}