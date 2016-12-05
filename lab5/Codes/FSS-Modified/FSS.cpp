/**
 * @brief Flow shop scheduling
 * @author doc. MSc. Donald Davendra Ph.D.
 * @date 3.10.2013
 *
 * This is a simple class to calculate the makespan of the flowshop scheduling schedule.
 */

/*! \file FSS.h
 \brief A FSS header file.
 */
#include "FSS.h"

#include <iostream>
#include <fstream>
#include <cmath>
#include <stdlib.h>

using namespace std;

cFSS::cFSS(){
}

void cFSS::Init(std::string file_path){

    ifstream infile;
    infile.open(file_path);

    if(!infile.is_open()) {
        cout << "Error Opening File.\n";
        exit(1);
    }
    else {
        infile >> m_Machines;
        infile >> m_Jobs;

        m_ProcessTime = new float*[m_Machines];
        for (int i = 0; i < m_Machines; i++) {
            m_ProcessTime[i] = new float[m_Jobs];
        }

        for (int i = 0; i < (m_Machines); i++) {
            for (int j = 0; j < m_Jobs; j++) {
                infile >> m_ProcessTime[i][j];
            }
        }

        m_CompletionTime = new float*[m_Machines];
        for (int i = 0; i < m_Machines; i++) {
            m_CompletionTime[i] = new float[m_Jobs];
        }
    }

    infile.close();
}

cFSS::~cFSS(){
    for (int i = 0; i < m_Machines; i++) {
        delete [] m_ProcessTime[i];
    }
    delete [] m_ProcessTime;
    
    for (int i = 0; i < m_Machines; i++) {
        delete [] m_CompletionTime[i];
    }
    delete [] m_CompletionTime;
}

int cFSS::GetMachines(){
    
    return m_Machines;
}

int cFSS::GetJobs(){
    
    return m_Jobs;
}

float cFSS::Makespan(int *Schedule){
    double max;
   
    Initialize();
    
    // Calculate processing time for all jobs on first machine
    m_CompletionTime[0][0] = m_ProcessTime[0][Schedule[0]-1];
    
    for (int i = 1; i < m_Jobs; i++) {
        m_CompletionTime[0][i] = (m_CompletionTime[0][i-1] + m_ProcessTime[0][Schedule[i]-1]);
    }
    
    // Calculate the processing time for first job on all machines
    
    for (int i = 1; i < m_Machines; i++) {
        m_CompletionTime[i][0] = (m_CompletionTime[i-1][0] + m_ProcessTime[i][Schedule[0]-1]);
    }
    
    // Calculate the rest of the processing time
    for (int i = 1; i < m_Machines; i++) {
        for (int j = 1; j < m_Jobs; j++) {
            max = Max(m_CompletionTime[i][j-1], m_CompletionTime[i-1][j]);
            m_CompletionTime[i][j] = m_ProcessTime[i][Schedule[j]-1] + max;
        }
    }

    // Return the makespan.
    return m_CompletionTime[m_Machines-1][m_Jobs-1];

}

void cFSS::Initialize(){
    for (int i = 0; i < m_Machines; i++) {
        for (int j = 0; j < m_Jobs; j++) {
            m_CompletionTime[i][j] = 0;
        }
        
    }

}

float cFSS::Max(float A,float B){
	if(A>=B)
		return A;
	else
		return B;
}
