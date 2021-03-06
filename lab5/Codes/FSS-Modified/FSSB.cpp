/**
 * @brief Flow shop with blocking
 * @author doc. MSc. Donald Davendra Ph.D.
 * @date 3.10.2013
 *
 * This is a simple class to calculate the makespan of the flowshop with blocking schedule.
 */


/*! \file FSSB.h
 \brief A FSSB header file.
 */
#include "FSSB.h"

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

cFSSB::cFSSB(){
}

void cFSSB::Init(std::string file_path){

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

cFSSB::~cFSSB(){
    for (int i = 0; i < m_Machines; i++) {
        delete [] m_ProcessTime[i];
    }
    delete [] m_ProcessTime;
    
    for (int i = 0; i < m_Machines; i++) {
        delete [] m_CompletionTime[i];
    }
    delete [] m_CompletionTime;
}

int cFSSB::GetMachines(){
    
    return m_Machines;
}

int cFSSB::GetJobs(){
    
    return m_Jobs;
}

float cFSSB::Makespan(int *Schedule){
    Initialize();
    
    // Calculate processing time for all jobs on first machine
    m_CompletionTime[0][0] = m_ProcessTime[0][Schedule[0]-1];
    
    for (int i = 1; i < m_Machines; i++) {
        m_CompletionTime[i][0] = (m_CompletionTime[i-1][0] + m_ProcessTime[i][Schedule[0]-1]);
    }
    
    // Calculate for each subsequent job
    for (int i = 1; i < m_Jobs; i++) {
        for (int j = 0; j < m_Machines; j++) {
            if(j == 0){
                m_CompletionTime[j][i] = m_CompletionTime[j][i-1] + m_ProcessTime[j][Schedule[i]-1];
            }
            else{
                if(m_CompletionTime[j-1][i] < m_CompletionTime[j][i-1]){
                    m_CompletionTime[j-1][i] = m_CompletionTime[j][i-1];
                }
                m_CompletionTime[j][i] = m_CompletionTime[j-1][i] + m_ProcessTime[j][Schedule[i]-1];
            }
        }
    }
    
    // Return the makespan.
    return m_CompletionTime[m_Machines-1][m_Jobs-1];

}

void cFSSB::Initialize(){
    for (int i = 0; i < m_Machines; i++) {
        for (int j = 0; j < m_Jobs; j++) {
            m_CompletionTime[i][j] = 0;
        }
        
    }

}
