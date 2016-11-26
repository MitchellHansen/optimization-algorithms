#pragma once
#include "search_function.h"

class firefly : public search_function {

public:

    firefly(function f) : search_function(f) {};

    double search(int permutations, int dimensionality) {

        // Set up random start population
        for (int p = 0; p < population_size; p++) {
            std::vector<double> tmp;
            for (int i = 0; i < dimensionality; i++){
                tmp.push_back(fmod(randomMT(), (func.upper_bound * 2)) + func.lower_bound);
            }
            population.push_back(tmp);
        }


        for (int t = 0; t < iterations; t++){

            // Compare each fly to each other
            for (int i = 0; i < population.size(); i++){
                for (int j = 0; j < population.size(); j++){

                    // If it finds one brighter
                    if (func.compute(population.at(j)) < func.compute(population.at(i))){

                        // Move towards it for each dimension
                        for (int d = 0; d < dimensionality; d++){

                            population.at(i).at(d) =
                                    population.at(i).at(d) +
                                    attractiveness(distance(population.at(i), population.at(j))) *
                                    (population.at(j).at(d) - population.at(i).at(d)) + alpha *
                                    rand_between(-0.5, 0.5);

                            check_solution_bounds(&population.at(i));
                        }
                    }
                }
            }
        }

        // Sort the population and return the best fitness
        std::sort(population.begin(), population.end(), [this](std::vector<double> a, std::vector<double> b){
            return this->func.compute(a) < this->func.compute(b);
        });
        return func.compute(population.front());
    };

private:

    // Distance between two vector points
    double distance(std::vector<double> a, std::vector<double> b){

        double sum = 0;
        for (int i = 0; i < a.size(); i++){
            sum += pow(a.at(i) - b.at(i), 2);
        }
        return sqrt(sum);
    }

    // Inverse square law basically
    double attractiveness(double distance){
        return beta * exp(-gamma * distance * distance);
    }

    // Constants
    double gamma = 1.0;
    double alpha = 0.5;
    double beta = 0.2;

    int iterations = 100;
    int population_size = 50;

    std::vector<std::vector<double>> population;
};







