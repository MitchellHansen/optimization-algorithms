/**
 * @brief Flow shop scheduling with no wait
 * @author doc. MSc. Donald Davendra Ph.D.
 * @date 3.10.2013
 *
 * This is a simple class to calculate the makespan of the flowshop with no wait schedule.
 */

#include <iostream>
#include "FSSNW.h"

using namespace std;

void JobMakespan(cFSSNW *FSS);

//! the main function.
/*!
 \return 0 for successful completion
 */
int main ()
{
    //! Initialization of the FSSNW class
    cFSSNW* FSSNW = new cFSSNW();
    
    //! Calculate a simple schedule
    JobMakespan(FSSNW);

    return 0;
}

//! Function to calculate a simple schedule.
/*!
 \return no return value
 */
void JobMakespan(cFSSNW *FSSNW){
    //! Initilaize a schedule
    int *Schedule = new int[FSSNW->GetJobs()];
    
    //! Fill the schedule sequentially
    for (int i = 0; i < FSSNW->GetJobs(); i++) {
        Schedule[i] = i+1;
    }
    //! Calculate the makespan of the simple schedule and display it in standard output
    cout << "The makespan is: " << FSSNW->Makespan(Schedule) << endl;
    
    //! Delete the schedule
    delete [] Schedule;

}
