#include<iostream>
#include<vector>
#include<sstream>
#include<string>
#include<utility>

/*
    Process structure, this is where the attributes of each process is stored
    at = arrival time
    bt = burst time
*/
struct Process{
    unsigned at = 0;
    unsigned bt = 0;
};
// Main function
int main(){
    // vector for input processes, it will store the raw input from the user
    std::vector<Process> processes;
    // vector to get the completion time of the process
    std::vector<unsigned> completion;
    // vector for the ready queue of each process, once the arrival time is met or
    // (time = at) the process will be pushed to the queue according to the Shortest Job First algorithm
    // it will store the original index of each process and their Process structure
    std::vector<Process> queue;
    // vector to store the result of turnaround time and waiting time of every processes
    std::vector<std::pair<unsigned, unsigned>> TTWT;
    /*
        time_sum = will compute for the completion time by adding the burst time of each process
        TT = temporary variable to store the turnaround time of the process
        at_num = temporary variable to store each input for arrival time
        bt_num = temporary variable to store each input for burst time
    */
    unsigned time_sum = 0, TT = 0, at_num, bt_num;
    // input variables for arrival time and burst time, input should be separated by spaces
    // input will be manipulated by the stringstream
    std::string arrival_t = "", burst_t = "";
    // inputting of arrival time and burst time
    std::cout << "Process Scheduling (FCFS)" << std::endl;
    std::cout << "Enter the arrival time: ";
    std::getline(std::cin >> std::ws, arrival_t);
    std::cout << "Enter the burst time: ";
    std::getline(std::cin >> std::ws, burst_t);
    // std::istringstream is used to separate a single input into multiple integers
    // it is used for inputs like arrival time and burst time
    std::stringstream ss_at(arrival_t);
    std::stringstream ss_bt(burst_t);
    // while loop for separation of inputs and storing those values in the processes vector
    // alongside with summing up the burst time of each processes
    while(ss_at >> at_num && ss_bt >> bt_num){
        Process p;
        p.at = at_num;
        p.bt = bt_num;
        processes.push_back(p);
        time_sum += bt_num;
    }
    // processing is the variable used to decrementing the burst time
    Process processing;
    unsigned time = 0; // time is used to for identifying the current seconds/milliseconds each loop
    size_t j = 0; // j will be used to traverse the processes vector
    // for loop for getting the completion time of the process by adding the burst of
    // correspoding processes, the sum will be pushed to the completion vector
    while(time < time_sum){
        while(time >= processes[j].at && j < processes.size()){
            queue.push_back(processes[j]);
            j++;
        }
        if(!queue.empty()){
            // the first element on the queue will be stored in the processing variable then decrements it
            processing = queue[0];
            // the while loop will decrement the process until reaching 0
            while(processing.bt > 0) {
                processing.bt--;
                time++;
            }
            // after the loop, the current time will be stored to the completion vector,
            // along with the process which is done processing then erase the process to the queue
            completion.push_back(time);
            queue.erase(queue.begin());
        } else {
            // Idle time, the excess time will be added to the total time to reach the end time of process
            time++;
            time_sum++;
        }
    }
    // for loop to compute for the turnaround time and waiting time for each processes
    // then adding it in the TTWT vector
    for(size_t i = 0; i < processes.size(); i++){
        TT = completion[i] - processes[i].at;
        TTWT.push_back(std::make_pair(TT, (TT - processes[i].bt)));
    }
    // Lastly, display all the contents of the process from the process ID to waiting time
    std::cout << "ID\t\tAT\t\tBT\t\tCT\t\tTT\t\tWT" << std::endl;
    for(size_t i = 0; i < processes.size(); i++){
        std::cout << "J" << i + 1 << "\t\t" << processes[i].at << "\t\t" << processes[i].bt <<
        "\t\t" << completion[i] << "\t\t" << TTWT[i].first << "\t\t" << TTWT[i].second << std::endl; 
    }
    return 0;
}