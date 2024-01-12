#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<utility>
#include<algorithm>

/*
    Process structure, this is where the attributes of each process is stored
    id = process id number
    at = arrival time
    bt = burst time
    pr = priority 
    cp = completion time
    tt = turnaround time
    wt = waiting time
*/
struct Process{
    unsigned id = 0;
    unsigned at = 0;
    unsigned bt = 0;
    unsigned pr = 0;
    unsigned cp = 0;
    unsigned tt = 0;
    unsigned wt = 0;
    void TTWT(const unsigned& completion_time){
        this->cp = completion_time;
        this->tt = this->cp - this->at;
        this->wt = this->tt - this->bt;
    }
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
        id_num = process id of each process, incrementation is done inside the while loop for separation of inputs
    */
    unsigned at_num, bt_num, pr_num, time_sum = 0, TT, id_num = 1;
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
    // checking if the number of arrival time is equal to the number of burst time and their sign
    int value;
    size_t size_at = 0, size_bt = 0, size_pr = 0;
    while (ss_at >> value) {
        if (value < 0) {
            throw std::runtime_error("Negative number found");
        } else size_at++;
    }
    while (ss_bt >> value) {
        if (value < 0) {
            throw std::runtime_error("Negative number found");
        } else size_bt++;
    }
    while (ss_pr >> value) {
        if (value < 0) {
            throw std::runtime_error("Negative number found");
        } else size_pr++;
    }
    if(size_at != size_bt || size_at != size_pr)
        throw std::out_of_range("Number of arrival time is not equal to number of burst time or priority");
    ss_at.clear();
    ss_at.seekg(0, std::ios::beg);
    ss_bt.clear();
    ss_bt.seekg(0, std::ios::beg);
    ss_pr.clear();
    ss_pr.seekg(0, std::ios::beg);
    // while loop for separation of inputs and storing those values in the processes vector
    // alongside with summing up the burst time of each processes
    while(ss_at >> at_num && ss_bt >> bt_num && ss_pr >> pr_num){
        Process p;
        p.id = id_num;
        p.at = static_cast<unsigned>(at_num);
        p.bt = static_cast<unsigned>(bt_num);
        p.pr = static_cast<unsigned>(pr_num);
        p.pr = pr_num;
        processes.push_back(p);
        time_sum += bt_num;
        id_num++;
    }
    size_t j = 0; // j will be used to traverse the processes vector
    // sorting the vector by their arrival time, if equal a.at == b.at it will base on id
    std::sort(processes.begin(), processes.end(), [](const Process& a, const Process& b)
    { return a.at < b.at || (a.at == b.at && a.id < b.id); });
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
            // decrementing the burst time of the first process in the queue
            queue[0].second.bt--;
            // if the burst time reach 0 it means its done, then the current time will be pushed to the completion vector
            // then erasing the first element in the queue, else moving the first element of the queue to the back of the queue
            if(queue[0].second.bt == 0){
                completion.push_back(std::make_pair(queue[0].first, time + 1));
                queue.erase(queue.begin());
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
    for(size_t i = 0; i < processes.size(); i++){
        processes[i].TTWT(completion[i].second);
    }
    // Lastly, display all the contents of the process from the process ID to waiting time
    std::cout << "ID\t\tAT\t\tBT\t\tPR\t\tCT\t\tTT\t\tWT" << std::endl;
    for(size_t i = 0; i < processes.size(); i++){
        std::cout << "J" << processes[i].id << "\t\t" << processes[i].at << "\t\t"
                << processes[i].bt << "\t\t" << processes[i].pr << "\t\t"
                << processes[i].cp << "\t\t" << processes[i].tt << "\t\t"
                << processes[i].wt << std::endl;
    }
    return 0;
}