#pragma once
#include "search_function.h"
struct particle {

    // Personal best
    double pb_fitness = 999999999999999;
    std::vector<double> pb_solution;

    // Current solution
    double fitness = 9999999999;
    std::vector<double> solution;

    std::vector<double> velocity;
    double v_max = 4.0;

    double c1 = 0.2;
    double c2 = 0.2;
    double weight = 0.9;

    int dimensionality;

    std::vector<double> *gb_solution;
    double *gb_fitness;

    function *func;

    particle(int dimensionality, std::vector<double> *gb_solution, double *gb_fitness, function *func) : dimensionality(dimensionality){

        this->gb_solution = gb_solution;
        this->gb_fitness = gb_fitness;
        this->func = func;

        // Blank initial solution and assign it also to pb
        pb_solution, solution = std::vector<double>(dimensionality, 0);

        // Init the velocity
        for (int i = 0; i < dimensionality; i++)
            velocity.push_back(rand_between(-v_max/3, v_max/3));

    }

    void update_fitness(){

        fitness = func->compute(solution);
        if (fitness < pb_fitness){
            pb_solution = solution;
            pb_fitness = fitness;
        }
        if (fitness < *gb_fitness){
            *gb_solution = solution;
            *gb_fitness = fitness;
        }
    }

    void update_velocity(){
        for (int d = 0; d < dimensionality; d++){
            velocity.at(d) = weight * velocity.at(d) + c1 * rand_between(0, 1) * (pb_solution.at(d) - solution.at(d)) +
                             c2 * rand_between(0, 1) * (gb_solution->at(d) - solution.at(d));
            if (velocity.at(d) > v_max)
                velocity.at(d) = v_max;
            else if (velocity.at(d) < -v_max)
                velocity.at(d) = -v_max;

            solution.at(d) += velocity.at(d);

            if (solution.at(d) < func->lower_bound)
                solution.at(d) = func->lower_bound;
            else if (solution.at(d) > func->upper_bound)
                solution.at(d) = func->upper_bound;
        }
    }
};
class particle_search : public search_function {


public:

    particle_search(function f) : search_function(f) {};

    double search(int permutations, int dimensionality) {

        for (int i = 0; i < number_of_particles; i++){

            particle p(dimensionality, &gb_solution, &gb_fitness, &func);
            p.solution = generate_solution(dimensionality);
            p.update_fitness();

            particles.push_back(p);

        }

        for (int i = 0; i < max_iterations; i++){

            for (int p = 0; p < particles.size(); p++){
                particles.at(p).update_fitness();
                particles.at(p).update_velocity();
            }
        }

        return gb_fitness;
    };

private:

    // The global best solution and fitness
    double gb_fitness = 99999999999999;
    std::vector<double> gb_solution;

    int number_of_particles = 100;
    std::vector<particle> particles;

    int max_iterations = 100;




};



























