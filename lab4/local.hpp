#pragma once
#include "search_function.h"

class local : public search_function {

public:
    local(function f) : search_function(f) {

    };

    double search(int permutations, int dimensionality) {

        // Set up the initial soution
        std::vector<double> best_solution;
        for (int i = 0; i < dimensionality; i++) {
            best_solution.push_back(fmod(randomMT(), (func.upper_bound * 2)) + func.lower_bound);
        }

        std::vector<double> temp_solution = best_solution;

        // While a better solution is being found
        bool better_solution_found = true;
        while (better_solution_found) {

            better_solution_found = false;
            double delta = 0.11;

            temp_solution = best_solution;
            std::vector<double> new_solution(dimensionality);

            for (int i = 0; i < dimensionality; i++) {

                temp_solution[i] += delta;
                new_solution[i] = best_solution[i] - delta * (func.compute(temp_solution) - func.compute(best_solution));
                temp_solution[i] = best_solution[i];
                // temp[i] - delta * new with delta, and the old without
            }

            // Check to see if we found a better solution
            if (func.compute(new_solution) < func.compute(best_solution)) {
                best_solution = new_solution;
                better_solution_found = true;
            }

        }

        return func.compute(best_solution);

    };

};


