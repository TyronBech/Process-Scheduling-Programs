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
    cp = completion time
    tt = turnaround time
    wt = waiting time
*/
struct Process{
    unsigned id = 0;
    unsigned at = 0;
    unsigned bt = 0;
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
    // (time = at) the process will be pushed to the queue according to the Round Robin algorithm
    // it will store the original index of each process and their Process structure
    std::vector<std::pair<size_t, Process>> queue;
    // vector to get the completion time and original index of the process, it is pair since
    // the queue doesn't store the processes by their index
    std::vector<std::pair<size_t, unsigned>> completion;
    // input variables for arrival time and burst time, input should be separated by spaces
    // input will be manipulated by the stringstream
    std::string arrival_t = "", burst_t = "";
    /*
        quantum = quantum time that will be allocated time for processing
        at_num = temporary variable to store each input for arrival time
        bt_num = temporary variable to store each input for burst time
        time_sum = variable to compute the total burst time of all process,
        it will be used in the for loop once the algorithm is started
        TT = temporary variable to store the turnaround time of each processes
        id_num = process id of each process, incrementation is done inside the while loop for separation of inputs
    */
    unsigned quantum, at_num, bt_num, time_sum = 0, TT, id_num = 1;
    // inputting of arrival time, burst time, and quantum time
    std::cout << "Process Scheduling (RR)" << std::endl;
    std::cout << "Enter arrival time: ";
    std::getline(std::cin >> std::ws, arrival_t);
    std::cout << "Enter burst time: ";
    std::getline(std::cin >> std::ws, burst_t);
    std::cout << "Enter quantum time: ";
    std::cin >> quantum;
    // std::istringstream is used to separate a single input into multiple integers
    // it is used for inputs like arrival time and burst time
    std::istringstream ss_at(arrival_t);
    std::istringstream ss_bt(burst_t);
    // while loop for separation of inputs and storing those values in the processes vector
    // alongside with summing up the burst time of each processes
    while(ss_at >> at_num && ss_bt >> bt_num){
        Process p;
        p.id = id_num;
        p.at = at_num;
        p.bt = bt_num;
        processes.push_back(p);
        time_sum += bt_num;
        id_num++;
    }
    // sorting the vector by their arrival time, if equal a.at == b.at it will base on id
    std::sort(processes.begin(), processes.end(), [](const Process& a, const Process& b)
    { return a.at < b.at || (a.at == b.at && a.id < b.id); });
    size_t j = 0; // j will be used to traverse the processes vector
    unsigned start = 0; // start will be the starting point of processing until it met the quantum time
                        // once reached, it will be reset into 0
    // for loop for Round Robin algorithm
    // it is based on time which means it starts by 0 seconds/milliseconds
    // up until the total burst time - 1
    for(unsigned time = 0; time < time_sum; ++time){
        // while the arrival time is equal to the current time, it will be pushed to the queue
        // getting ready for processing
        while(time == processes[j].at){
            queue.push_back(std::make_pair(j, processes[j]));
            j++;
        }
        if(!queue.empty()){
            // if the start reached the quantum time, the process will be pushed at the back
            // of the queue and reset the start to 0
            if(start >= quantum){
                queue.push_back(queue[0]);
                queue.erase(queue.begin());
                start = 0;
            }
            // as long as the queue is not empty the queue at index 0 will decrement its own burst time by 1
            // incrementing the start and checking if the process is done processing, once done the
            // queue at index 0 will be deleted, the current time will be pushed to the completion vector
            // along with the original index, and the start will reset by 0
            queue[0].second.bt--;
            start++;
            if(queue[0].second.bt == 0){
                completion.push_back(std::make_pair(queue[0].first, time + 1));
                queue.erase(queue.begin());
                start = 0;
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
    std::cout << "ID\t\tAT\t\tBT\t\tCT\t\tTT\t\tWT" << std::endl;
    for (size_t i = 0; i < processes.size(); i++) {
        std::cout << "J" << processes[i].id << "\t\t" << processes[i].at << "\t\t"
                  << processes[i].bt << "\t\t" << processes[i].cp << "\t\t"
                  << processes[i].tt << "\t\t" << processes[i].wt << std::endl;
    }
    return 0;
}