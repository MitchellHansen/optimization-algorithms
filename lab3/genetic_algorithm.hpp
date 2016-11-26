#pragma once
#include "search_function.h"

class genetic_algorithm : public search_function {

public:

    genetic_algorithm(function f) : search_function(f) {};

    double search(int permutations, int dimensionality) {

        elitism = elitism_rate * number_of_solutions;

        // Set up random start population
        std::vector<std::vector<double>> population;
        for (int p = 0; p < number_of_solutions; p++) {
            std::vector<double> tmp;
            for (int i = 0; i < dimensionality; i++){
                tmp.push_back(fmod(randomMT(), (func.upper_bound * 2)) + func.lower_bound);
            }
            population.push_back(tmp);
        }


        for (int i = 0; i < max_iterations; i++){

            // Setup the random new population
            std::vector<std::vector<double>> new_population;
            for (int p = 0; p < number_of_solutions; p++) {
                std::vector<double> tmp;
                for (int i = 0; i < dimensionality; i++){
                    tmp.push_back(fmod(randomMT(), (func.upper_bound * 2)) + func.lower_bound);
                }
                new_population.push_back(tmp);
            }

            for (int s = 0; s < number_of_solutions; s += 2){

                auto p1p2 = select(&population);

                crossover(&std::get<0>(p1p2), &std::get<1>(p1p2));

                mutate(&std::get<0>(p1p2));
                mutate(&std::get<1>(p1p2));

            }

            reduce(&population, &new_population);

            for (auto q: population){
                double val = func.compute(q);
                if (val < best_fitness)
                    best_fitness = val;
            }
        }

        return best_fitness;
    };


private:

    double crossover_rate = 0.90;
    double elitism_rate = 0.2;
    int elitism = 10;
    double mutation_rate = 0.008;
    double mutation_range = 0.1;
    double muration_precision = 3.5;
    double best_fitness = 99999999999999999;
    int number_of_solutions = 50;
    int max_iterations = 100;


    double get_fitness(std::vector<std::vector<double>> *population){

        double fitness_sum = 0;

        for (auto p: *population){
            double fitness = func.compute(p);
            if (fitness >= 0)
                fitness_sum += 1 / (1 + fitness);
            else
                fitness_sum += 1 + abs(fitness);
        }

        return fitness_sum;
    }

    int select_parent(std::vector<std::vector<double>> *population){

        double r = fmod(randomMT(), total_fitness(population));

        int s = 0;

        while (s < population->size()-1 && (r - func.compute(population->at(s)) > 0)) {
            r -= func.compute(population->at(s++));
        }

        return s;
    }

    std::tuple<std::vector<double>, std::vector<double>> select(std::vector<std::vector<double>> *population){

        auto p1 = population->at(select_parent(population));
        auto p2 = population->at(select_parent(population));

        return std::make_tuple(p1, p2);
    };

    void mutate(std::vector<double> *solution){
        for (auto i: *solution){
            if ((randomMT() * 1.0 / UINT32_MAX) < mutation_rate){
                i += ((randomMT() * 1.0 / UINT32_MAX) * 2 - 1) * (func.upper_bound - func.lower_bound) *
                     mutation_range * pow(2, (-1 * (randomMT() * 1.0 / UINT32_MAX) * muration_precision));
            }
        }
    }

    void crossover(std::vector<double> *parent1, std::vector<double> *parent2){

        if ((randomMT() * 1.0 / UINT32_MAX) < crossover_rate){

            int d = randomMT() % (parent1->size() - 1) + 1;
            int dim = parent1->size();

            std::vector<double> temp;
            temp.insert(temp.begin(), parent1->begin(), parent1->begin() + d);

            parent1->erase(parent1->begin(), parent1->begin() + d);
            parent1->insert(parent1->end(), parent2->begin() + dim - d, parent2->end());

            parent2->erase(parent2->begin() + dim - d, parent2->end());
            parent2->insert(parent2->end(), temp.begin(), temp.end());
        }
    }

    void reduce(std::vector<std::vector<double>> *population, std::vector<std::vector<double>> *new_population){

        std::sort(population->begin(), population->end(), [this](std::vector<double> a, std::vector<double> b){
            return this->func.compute(a) < this->func.compute(b);
        });

        std::sort(new_population->begin(), new_population->end(), [this](std::vector<double> a, std::vector<double> b){
            return this->func.compute(a) < this->func.compute(b);
        });

        for (int s = 0; s < elitism; s++) {
            new_population->at(elitism + 1 - s) = population->at(s);
        }

        *population = *new_population;

    }

    double total_fitness(std::vector<std::vector<double>> *population){

        double val = 0;

        for (auto i: *population)
            val += func.compute(i);

        return val;
    }
};



