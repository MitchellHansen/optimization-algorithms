/**
 * @brief Flow shop scheduling
 * @author doc. MSc. Donald Davendra Ph.D.
 * @date 3.10.2013
 *
 * This is a simple class to calculate the makespan of the flowshop scheduling schedule.
 */

#ifndef __FSS_H__
#define __FSS_H__

#include <string>

class cFSS{
	
public:
    //! A constructor.
    /*!
     Constructs the FSS class, and assigns the values.
     */
	cFSS();

    void Init(std::string file_path);
    
    //! A destructor.
    /*!
    Clears the memory.
     */
	~cFSS();
    
    //! A normal member taking in the schedule and returning the makespan.
    /*!
     \param the schedule
     \return The cost of the tours
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
    float Max(float, float);
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
