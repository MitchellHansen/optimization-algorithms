#pragma once
#include "search_function.h"

class differential_evolution : public search_function {

public:

    differential_evolution(function f) : search_function(f) {};

    double search(int permutations, int dimensionality) {

        // Set up random start
        std::vector<std::vector<double>> population = generate_population(50, dimensionality);

        for (int g = 0; g < maximum_generation_number; g++) {

            for (int i = 0; i < population.size(); i++) {

                // Create the U, temp vector to hold values
                std::vector<double> u(dimensionality, 0);

                // select a random dimension
                int j_rand = rand() % dimensionality;

                for (int j = j_rand; j < dimensionality; j++){

                    // Accept changes if rng returns < 0.9
                    if (randomMT() * 1.0 / RAND_MAX < 0.9)
                        u.at(j) = check_bounds(compute_with_strategy(&population, j, i));
                    else
                        u.at(j) = population.at(i).at(j);

                }

                // If the new population has a better fitness, replace it
                if (func.compute(population.at(i)) > func.compute(u))
                    population.at(i) = u;

            }
        }

        // Generation is done, return the best value from the population
        std::sort(population.begin(), population.end(), [this](std::vector<double> a, std::vector<double> b){
            return this->func.compute(a) < this->func.compute(b);
        });

        return func.compute(population[0]);
    };

    void set_strategy(int strategy){
        this->strategy = strategy;
    }

private:

    // G
    int maximum_generation_number = 30;

    // Tuning variable
    double tuning_variable_f = 0.8;
    double tuning_variable_lambda = 1.0;

    int strategy = 0;

    // Compute using different strategies
    double compute_with_strategy(std::vector<std::vector<double>> *population, int j, int i){

        // Setup and find the best solution in the population that was passed in
        std::vector<double> best_solution;
        double best_fitness = 999999999999;

        for (auto p: *population){
            double val = func.compute(p);

            if (val < best_fitness){
                best_fitness = val;
                best_solution = p;
            }
        }

        // Depending on the strategy, determine the new solution at J
        switch(strategy){
            case 1: {
                std::vector<int> r = distinct_indices(2, population[0].size());
                return best_solution[j] + tuning_variable_f * (population->at(r[0]).at(j) - population->at(r[1]).at(j));
            }
            case 2: {
                std::vector<int> r = distinct_indices(3, population[0].size());
                return population->at(r[0]).at(j) + tuning_variable_f * (population->at(r[1]).at(j) - population->at(r[2]).at(j));
            }
            case 3:{
                std::vector<int> r = distinct_indices(2, population[0].size());
                return population->at(i).at(j) + tuning_variable_lambda * (best_solution.at(j) - population->at(i).at(j)) + tuning_variable_f * (population->at(r[0]).at(j) - population->at(r[1]).at(j));
            }
            case 4:{
                std::vector<int> r = distinct_indices(4, population[0].size());
                return best_solution.at(j) + tuning_variable_f * (population->at(r[0]).at(j) + population->at(r[1]).at(j) - population->at(r[2]).at(j) - population->at(r[3]).at(j));
            }
            case 5:{
                std::vector<int> r = distinct_indices(5, population[0].size());
                return population->at(r[4]).at(j) + tuning_variable_f * (population->at(r[0]).at(j) + population->at(r[1]).at(j) - population->at(r[2]).at(j) - population->at(r[3]).at(j));
            }
            case 6:{
                std::vector<int> r = distinct_indices(2, population[0].size());
                return best_solution.at(j) + tuning_variable_f * (population->at(r[0]).at(j) - population->at(r[1]).at(j));
            }
            case 7:{
                std::vector<int> r = distinct_indices(3, population[0].size());
                return population->at(r[0]).at(j) + tuning_variable_f * (population->at(r[1]).at(j) - population->at(r[2]).at(j));
            }
            case 8:{
                std::vector<int> r = distinct_indices(2, population[0].size());
                return population->at(i).at(j) + tuning_variable_lambda * (best_solution.at(j) - population->at(i).at(j)) + tuning_variable_f * (population->at(r[0]).at(j) - population->at(r[1]).at(j));
            }
            case 9:{
                std::vector<int> r = distinct_indices(4, population[0].size());
                return best_solution.at(j) + tuning_variable_f * (population->at(r[0]).at(j) + population->at(r[1]).at(j) - population->at(r[2]).at(j) - population->at(r[3]).at(j));
            }
            case 10:{
                std::vector<int> r = distinct_indices(5, population[0].size());
                return population->at(r[4]).at(j) + tuning_variable_f * (population->at(r[0]).at(j) + population->at(r[1]).at(j) - population->at(r[2]).at(j) - population->at(r[3]).at(j));
            }
        }
    }

    std::vector<int> distinct_indices(int count, int max){

        std::vector<int> indices;
        for (int q = 0; q < count; q++) {
            int val = 1 + (rand() % (max - 1));
            while (std::count(indices.begin(), indices.end(), val) != 0)
                val = randomMT() % max;
            indices.push_back(val);
        }
        return indices;
    }

};































