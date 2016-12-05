/**
 * @brief Flow shop with blocking
 * @author doc. MSc. Donald Davendra Ph.D.
 * @date 3.10.2013
 *
 * This is a simple class to calculate the makespan of the flowshop with blocking schedule.
 */

#include <iostream>
#include "FSSB.h"

using namespace std;

void JobMakespan(cFSSB *FSS);

//! the main function.
/*!
 \return 0 for successful completion
 */
int main ()
{
    //! Initialization of the FSSB class
    cFSSB* FSSB = new cFSSB();
    
    //! Calculate a simple schedule
    JobMakespan(FSSB);

    return 0;
}

//! Function to calculate a simple schedule.
/*!
 \return no return value
 */
void JobMakespan(cFSSB *FSSB){
    //! Initialize a schedule
    int *Schedule = new int[FSSB->GetJobs()];
    
    //! Fill the schedule sequentially
    for (int i = 0; i < FSSB->GetJobs(); i++) {
        Schedule[i] = i+1;
    }
    //! Calculate the makespan of the simple schedule and display it in standard output
    cout << "The makespan is: " << FSSB->Makespan(Schedule) << endl;
    
    //! Delete the schedule.
    delete [] Schedule;

}
