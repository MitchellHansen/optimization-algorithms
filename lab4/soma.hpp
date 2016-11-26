#pragma once
#include "search_function.h"

class soma : public search_function {

public:

    soma(function f) : search_function(f) {};

    double search(int permutations, int dimensionality) {

        // Set the parameters defined on page 8
        path_length = 3.5;
        specimen_step = 0.11;
        perturbation = 0.11;
        migrations = 1000;
        min_div = 0.1;

        // Set the population size
        population_size = dimensionality * 0.5;
        if (population_size < 10)
            population_size = 10;

        // Set up random start population
        for (int p = 0; p < population_size; p++) {
            std::vector<double> tmp;
            for (int i = 0; i < dimensionality; i++){
                tmp.push_back(fmod(randomMT(), (func.upper_bound * 2)) + func.lower_bound);
            }
            population.push_back(tmp);
        }

        // Sort the population so the leader is at(0)
        std::sort(population.begin(), population.end(), [this](std::vector<double> a, std::vector<double> b){
            return this->func.compute(a) < this->func.compute(b);
        });

        for (int m = 0; m < migrations; m++){

            std::vector<double> leader_solution = population.at(0);
            double leader_fitness = func.compute(leader_solution);

            for (int i = 1; i < population.size(); i++){

                // We need the best fitness and the starting point for each
                // individual in the population. start_solution is not mutated,
                // while best_* and population.at(i) both are
                double best_fitness = func.compute(population.at(i));
                std::vector<double> best_solution = population.at(i);
                std::vector<double> start_solution = population.at(i);

                for (double p = 0; p < path_length; p += specimen_step){

                    // Generate the perturbation vector for each step,
                    // seems to give better results than per migration
                    std::vector<double> perturbation_vector(dimensionality, 0);
                    for (auto &q: perturbation_vector){
                        double val = rand_between(0, 1);
                        if (val < perturbation)
                            q = 1;
                        else
                            q = 0;
                    }

                    // Mutate the individual
                    for (int j = 0; j < dimensionality; j++){
                        population.at(i).at(j) = start_solution.at(j) + (leader_solution.at(j) - start_solution.at(j)) * p * perturbation_vector.at(j);
                    }

                    check_solution_bounds(&population.at(i));


                    // If this step beat the individuals best, update it
                    if (func.compute(population.at(i)) < best_fitness){
                        best_fitness = func.compute(population.at(i));
                        best_solution = population.at(i);
                    }
                }

                // population.at(i) is now at the end of the step.
                // set it to the best solution it found along the way
                population.at(i) = best_solution;

            }

            // Early exit if the different between the leader and any others are less than
            // a defined constant. 1 is a little to lenient.
            for (int r = 1; r < population.size(); r++){
                if (std::abs(func.compute(population.at(r)) - leader_fitness) < min_div){
                    return leader_fitness;
                }
            }

            // Resort the population so the leader will be at(0)
            std::sort(population.begin(), population.end(), [this](std::vector<double> a, std::vector<double> b){
                return this->func.compute(a) < this->func.compute(b);
            });

            // Test the front position. If the leader was usurped then replace it.
            if (func.compute(population.front()) < leader_fitness) {
                leader_solution = population.front();
                leader_fitness = func.compute(leader_solution);
            }

        }

        // Return the best solution found
        return func.compute(population.front());
    };

private:

    double specimen_step;
    double path_length;
    int population_size;
    double perturbation;
    double min_div;
    int migrations;

    std::vector<std::vector<double>> population;

};



























