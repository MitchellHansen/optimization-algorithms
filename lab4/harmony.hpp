#pragma once
#include "search_function.h"

class harmony : public search_function {

public:

    harmony(function f) : search_function(f) {};

    double search(int permutations, int dimensionality) {

        this->dimensionality = dimensionality;

        // Set up random start population
        for (int p = 0; p < population_size; p++) {
            std::vector<double> tmp;
            for (int i = 0; i < dimensionality; i++){
                tmp.push_back(fmod(randomMT(), (func.upper_bound * 2)) + func.lower_bound);
            }
            population.push_back(tmp);
        }

        double best_fitness = func.compute(population.at(0));

        // Do a thousand iterations
        int r = 0;
        while (r < 1000){

            // The rng to determine which of the 3 we chose
            double rng = rand_between(0, 1);

            // Accept up the the specified percentage, re init the rest
            if (rng > r_accept) {
                accept_and_generate();
            }

            // Harmonize
            else if (rng > r_pa) {
                for (int p = 0; p < population.size(); p++) {
                    for (int d = 0; d < dimensionality; d++) {
                        population.at(p).at(d) = population.at(p).at(d) + rand_between(1, 2) * rand_between(-1, 1);
                    }
                }
            }

            // Introduce some stochasticity
            else{
                population.clear();
                for (int p = 0; p < population_size; p++) {
                    std::vector<double> tmp;
                    for (int i = 0; i < dimensionality; i++){
                        tmp.push_back(fmod(randomMT(), (func.upper_bound * 2)) + func.lower_bound);
                    }
                    population.push_back(tmp);
                }
            }

            // Sort the array and find the best fitness, record
            std::sort(population.begin(), population.end(), [this](std::vector<double> a, std::vector<double> b){
                return this->func.compute(a) < this->func.compute(b);
            });

            if (func.compute(population.at(0)) < best_fitness)
                best_fitness = func.compute(population.at(0));

            r++;
        }


        return func.compute(population.at(0));
    };

private:

    double r_accept = 0.8;
    double r_pa = 0.1;

    int population_size = 50;
    int dimensionality = 0;

    void accept_and_generate(){

        // Resort the population so the best will be at(0)
        std::sort(population.begin(), population.end(), [this](std::vector<double> a, std::vector<double> b){
            return this->func.compute(a) < this->func.compute(b);
        });

        // Keep up to the accept rate
        std::vector<std::vector<double>> tmp_pop;
        for (int i = 0; (1.0 * i / population.size()) < r_accept; i++){
            tmp_pop.push_back(population.at(i));
        }

        // Repopulate with random values
        for (int p = 0; p < population_size - tmp_pop.size(); p++) {
            std::vector<double> tmp;
            for (int i = 0; i < dimensionality; i++){
                tmp.push_back(fmod(randomMT(), (func.upper_bound * 2)) + func.lower_bound);
            }
            tmp_pop.push_back(tmp);
        }

        population = tmp_pop;


    }


    std::vector<std::vector<double>> population;

};



























