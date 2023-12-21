#include<iostream>
#include<vector>
#include<sstream>
#include<string>
#include<utility>

// Main function
int main(){
    // vector for input processes, it will store the raw input from the user
    std::vector<std::pair<size_t, unsigned>> processes;
    // vector to get the completion time of the process
    std::vector<unsigned> completion;
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
        processes.push_back(std::make_pair(at_num, bt_num));
    }
    // for loop for getting the completion time of the process by adding the burst of
    // correspoding processes, the sum will be pushed to the completion vector
    for(size_t i = 0; i < processes.size(); i++){
        time_sum += processes[i].second;
        completion.push_back(time_sum);
    }
    // for loop to compute for the turnaround time and waiting time for each processes
    // then adding it in the TTWT vector
    for(size_t i = 0; i < processes.size(); i++){
        TT = completion[i] - processes[i].first;
        TTWT.push_back(std::make_pair(TT, (TT - processes[i].second)));
    }
    // Lastly, display all the contents of the process from the process ID to waiting time
    std::cout << "ID\t\tAT\t\tBT\t\tCT\t\tTT\t\tWT" << std::endl;
    for(size_t i = 0; i < processes.size(); i++){
        std::cout << "J" << i + 1 << "\t\t" << processes[i].first << "\t\t" << processes[i].second <<
        "\t\t" << completion[i] << "\t\t" << TTWT[i].first << "\t\t" << TTWT[i].second << std::endl; 
    }
    return 0;
}