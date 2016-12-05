/**
 * @brief Flow shop scheduling
 * @author doc. MSc. Donald Davendra Ph.D.
 * @date 3.10.2013
 *
 * This is a simple class to calculate the makespan of the flowshop scheduling schedule.
 */

#include <iostream>
#include "FSS.h"
#include "FSSB.h"
#include "FSSNW.h"
#include <vector>
#include <chrono>
#include <thread>
#include <iostream>

using Clock = std::chrono::steady_clock;
using std::chrono::time_point;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using namespace std;

void JobMakespan(cFSS *FSS);
void JobMakespan(cFSSB *FSSB);
void JobMakespan(cFSSNW *FSSNW);

//! the main function.
/*!
 \return 0 for successful completion
 */
int main ()
{

    //! Initialization of the FSS* classes
    cFSS* FSS = new cFSS();
    cFSSB* FSSB = new cFSSB();
    cFSSNW* FSSNW = new cFSSNW();

    std::vector<int> times;

    std::cout << "FSS: Tests 1 through 120" << std::endl;
    for (int i = 1; i < 121; i++){
        FSS->Init("../TaillardDataSets/" + to_string(i) + ".txt");

        //! Calculate the schedule and print out results
        //std::cout << i << " : ";
        auto start = std::chrono::system_clock::now();

        JobMakespan(FSS);

        times.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count());

        std::cout << std::endl;
    }

    for (auto t: times){
        std::cout << t << std::endl;
    }
    times.clear();

    std::cout << "FSSB: Tests 1 through 120" << std::endl;
    for (int i = 1; i < 121; i++){
        FSSB->Init("../TaillardDataSets/" + to_string(i) + ".txt");

        //! Calculate the schedule and print out results
        //std::cout << i << " : ";
        auto start = std::chrono::system_clock::now();

        JobMakespan(FSSB);

        times.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count());
        std::cout << std::endl;
    }


    for (auto t: times){
        std::cout << t << std::endl;
    }
    times.clear();

    std::cout << "FSSNW: Tests 1 through 120" << std::endl;
    for (int i = 1; i < 121; i++){
        FSSNW->Init("../TaillardDataSets/" + to_string(i) + ".txt");

        //! Calculate the schedule and print out results
        //std::cout << i << " : ";
        auto start = std::chrono::system_clock::now();

        JobMakespan(FSSNW);

        times.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count());
        std::cout << std::endl;
    }


    for (auto t: times){
        std::cout << t << std::endl;
    }
    times.clear();

    return 0;
}

//! Function to calculate a simple schedule.
/*!
 \return no return value
 */
void JobMakespan(cFSS *FSS){

    //! Initilaize a schedule
    int *Schedule = new int[FSS->GetJobs()];
    
    //! Fill the schedule with it empty
    for (int i = 0; i < FSS->GetJobs(); i++) {
        Schedule[i] = 0;
    }

    // Determine if 1 or 2 should come first
    Schedule[0] = 1;
    Schedule[1] = 2;
    int first = FSS->Makespan(Schedule);

    Schedule[0] = 2;
    Schedule[1] = 1;
    int second = FSS->Makespan(Schedule);

    if (first > second){
        Schedule[0] = 1;
        Schedule[1] = 2;
    }

    //            for (int p = 0; p < FSS->GetJobs(); p++){
//                std::cout << Schedule[p] << " ";
//            }
//            std::cout << "     " << FSS->Makespan(Schedule) << std::endl;

    // Now walk through the remaining K's and determine their makespans
    for (int k = 3; k < FSS->GetJobs()+1; k++){

        // The initial value
        int best_val = INT32_MAX;
        int best_ind = -1;

        Schedule[k-1] = k;

        if (FSS->Makespan(Schedule) <= best_val){
            best_val = FSS->Makespan(Schedule);
            best_ind = k;
        }

        // Walk down to index 0
        for (int i = k-1; i > 0; i--){
            int f = Schedule[i-1];
            Schedule[i-1] = k;
            Schedule[i] = f;

            if (FSS->Makespan(Schedule) <= best_val){
                best_val = FSS->Makespan(Schedule);
                best_ind = i;
            }
        }

        // And then walk back up to the best index we found
        for (int i = 0; i < best_ind-1; i++) {
            int f = Schedule[i + 1];
            Schedule[i + 1] = k;
            Schedule[i] = f;
        }
    }

    //! Calculate the makespan of the simple schedule and display it in standard output
    cout << FSS->Makespan(Schedule);
    
    //! Delete the schdule.
    delete [] Schedule;

}

//! Function to calculate a simple schedule.
/*!
 \return no return value
 */
void JobMakespan(cFSSNW *FSSNW){

    //! Initilaize a schedule
    int *Schedule = new int[FSSNW->GetJobs()];

    //! Fill the schedule with it empty
    for (int i = 0; i < FSSNW->GetJobs(); i++) {
        Schedule[i] = 0;
    }

    // Determine if 1 or 2 should come first
    Schedule[0] = 1;
    Schedule[1] = 2;
    int first = FSSNW->Makespan(Schedule);

    Schedule[0] = 2;
    Schedule[1] = 1;
    int second = FSSNW->Makespan(Schedule);

    if (first > second){
        Schedule[0] = 1;
        Schedule[1] = 2;
    }

    //            for (int p = 0; p < FSS->GetJobs(); p++){
//                std::cout << Schedule[p] << " ";
//            }
//            std::cout << "     " << FSS->Makespan(Schedule) << std::endl;

    // Now walk through the remaining K's and determine their makespans
    for (int k = 3; k < FSSNW->GetJobs()+1; k++){

        // The initial value
        int best_val = INT32_MAX;
        int best_ind = -1;

        Schedule[k-1] = k;

        if (FSSNW->Makespan(Schedule) <= best_val){
            best_val = FSSNW->Makespan(Schedule);
            best_ind = k;
        }

        // Walk down to index 0
        for (int i = k-1; i > 0; i--){
            int f = Schedule[i-1];
            Schedule[i-1] = k;
            Schedule[i] = f;

            if (FSSNW->Makespan(Schedule) <= best_val){
                best_val = FSSNW->Makespan(Schedule);
                best_ind = i;
            }
        }

        // And then walk back up to the best index we found
        for (int i = 0; i < best_ind-1; i++) {
            int f = Schedule[i + 1];
            Schedule[i + 1] = k;
            Schedule[i] = f;
        }
    }

    //! Calculate the makespan of the simple schedule and display it in standard output
    cout << FSSNW->Makespan(Schedule);

    //! Delete the schdule.
    delete [] Schedule;

}

//! Function to calculate a simple schedule.
/*!
 \return no return value
 */
void JobMakespan(cFSSB *FSSB){

    //! Initilaize a schedule
    int *Schedule = new int[FSSB->GetJobs()];

    //! Fill the schedule with it empty
    for (int i = 0; i < FSSB->GetJobs(); i++) {
        Schedule[i] = 0;
    }

    // Determine if 1 or 2 should come first
    Schedule[0] = 1;
    Schedule[1] = 2;
    int first = FSSB->Makespan(Schedule);

    Schedule[0] = 2;
    Schedule[1] = 1;
    int second = FSSB->Makespan(Schedule);

    if (first > second){
        Schedule[0] = 1;
        Schedule[1] = 2;
    }

    //            for (int p = 0; p < FSS->GetJobs(); p++){
//                std::cout << Schedule[p] << " ";
//            }
//            std::cout << "     " << FSS->Makespan(Schedule) << std::endl;

    // Now walk through the remaining K's and determine their makespans
    for (int k = 3; k < FSSB->GetJobs()+1; k++){

        // The initial value
        int best_val = INT32_MAX;
        int best_ind = -1;

        Schedule[k-1] = k;

        if (FSSB->Makespan(Schedule) <= best_val){
            best_val = FSSB->Makespan(Schedule);
            best_ind = k;
        }

        // Walk down to index 0
        for (int i = k-1; i > 0; i--){
            int f = Schedule[i-1];
            Schedule[i-1] = k;
            Schedule[i] = f;

            if (FSSB->Makespan(Schedule) <= best_val){
                best_val = FSSB->Makespan(Schedule);
                best_ind = i;
            }
        }

        // And then walk back up to the best index we found
        for (int i = 0; i < best_ind-1; i++) {
            int f = Schedule[i + 1];
            Schedule[i + 1] = k;
            Schedule[i] = f;
        }
    }

    //! Calculate the makespan of the simple schedule and display it in standard output
    cout << FSSB->Makespan(Schedule);

    //! Delete the schdule.
    delete [] Schedule;

}