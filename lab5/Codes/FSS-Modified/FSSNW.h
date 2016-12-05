/**
 * @brief Flow shop scheduling with no wait
 * @author doc. MSc. Donald Davendra Ph.D.
 * @date 3.10.2013
 *
 * This is a simple class to calculate the makespan of the flowshop with no wait schedule.
 */

#ifndef __FSSNW_H__
#define __FSSNW_H__
#include <string>

class cFSSNW{
	
public:
    //! A constructor.
    /*!
     Constructs the FSSNW class, and assigns the values.
     */
	cFSSNW();

    void Init(std::string file_path);
    
    //! A destructor.
    /*!
    Clears the memory.
     */
	~cFSSNW();
    
    //! A normal member taking in the schedule and returning the cost.
    /*!
     \param A flowshop schedule
     \return The makespan value
     */
	float Makespan(int *Schedule);
    
    //! Returns the number of jobs.
    /*!
     \param no parameters
     \return The number of jobs
     */
    int GetJobs();
    
    //! Returns the number of machines.
    /*!
     \param no parameters
     \return The number of machines
     */
    int GetMachines();
    void Initialize();
	
private:
    //! The processing time matrix.
	float** m_ProcessTime;
    //! The completion time matrix.
    float** m_CompletionTime;
    //! The number of jobs.
    int m_Jobs;
    //! The number of machines.
    int m_Machines;
};

#endif
