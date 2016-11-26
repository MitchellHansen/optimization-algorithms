#pragma once
#include "search_function.h"

class iterative_local_search : public search_function {

public:

    iterative_local_search(function f) : search_function(f) {};

    double search(int permutations, int dimensionality) {

        // Set up random start
        std::vector<double> global_best_solution;
        for (int i = 0; i < dimensionality; i++) {
            global_best_solution.push_back(fmod(randomMT(), (func.upper_bound * 2)) + func.lower_bound);
        }


        // 30 iteration max
        int iteration_max = 30;
        for (int i = 0; i < iteration_max; i++){

            // Random new solution
            std::vector<double> best_solution;
            for (int i = 0; i < dimensionality; i++) {
                best_solution.push_back(fmod(randomMT(), (func.upper_bound * 2)) + func.lower_bound);
            }

            std::vector<double> temp_solution = best_solution;

            // While a better solution is still being found
            bool better_solution_found = true;
            while (better_solution_found) {

                better_solution_found = false;
                double delta = 0.11;

                temp_solution = best_solution;
                std::vector<double> new_solution(dimensionality);

                // Set up the new solution
                for (int i = 0; i < dimensionality; i++) {

                    temp_solution[i] += delta;
                    new_solution[i] = best_solution[i] - delta * (func.compute(temp_solution) - func.compute(best_solution));
                    temp_solution[i] = best_solution[i];
                    // temp[i] - delta * new with delta, and the old without
                }

                // test it
                if (func.compute(new_solution) < func.compute(best_solution)) {
                    best_solution = new_solution;
                    better_solution_found = true;
                }
            }

            // Check to see if we found a better global solution
            if (func.compute(best_solution) < func.compute(global_best_solution)){
                global_best_solution = best_solution;
            }
        }
    };
};


