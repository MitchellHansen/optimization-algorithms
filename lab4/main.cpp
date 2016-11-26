#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <chrono>
#include <cstring>
#include "twister.c"
#include "util.hpp"
#include "functions.hpp"
#include "random_walk.hpp"
#include "local.hpp"
#include "iterative_local.hpp"
#include "differential_evolution.hpp"
#include "genetic_algorithm.hpp"
#include "particle_swrm.hpp"
#include "soma.hpp"
#include "harmony.hpp"
#include "firefly.hpp"

int main(int argc, char* args[]) {

    std::map<int, function> function_lookup;

    function_lookup.emplace(std::make_pair(0, function(&schwefel, 512, -512)));
    function_lookup.emplace(std::make_pair(1, function(&first_de_jong, 100, -100)));
    function_lookup.emplace(std::make_pair(2, function(&rosenbrock, 100, -100)));
    function_lookup.emplace(std::make_pair(3, function(&rastrigin, 30, -30)));
    function_lookup.emplace(std::make_pair(4, function(&griewangk, 500, -500)));
    function_lookup.emplace(std::make_pair(5, function(&sine_envelope_sine_wave, 30, -30)));
    function_lookup.emplace(std::make_pair(6, function(&stretched_v_sine_wave, 30, -30)));
    function_lookup.emplace(std::make_pair(7, function(&ackleys_one, 32, -32)));
    function_lookup.emplace(std::make_pair(8, function(&ackleys_two, 32, -32)));
    function_lookup.emplace(std::make_pair(9, function(&egg_holder, 500, -500)));
    function_lookup.emplace(std::make_pair(10, function(&rana, 500, -500)));
    function_lookup.emplace(std::make_pair(11, function(&pathological, 100, -100)));
    function_lookup.emplace(std::make_pair(12, function(&michalewicz, M_PI, 0)));
    function_lookup.emplace(std::make_pair(13, function(&masters_cosine_wave, 30, -30)));
    function_lookup.emplace(std::make_pair(14, function(&shekels_foxholes, 10, 0)));

    function f;
    int dimensionality = 0;
    double seed = 0;
    int search_function = 0;

//    // Get the command line args
//    if (argc == 1){
//        char arg_str[200];
//        std::cin.get(arg_str, 200);
//        char t = ' ';
//
//        f = function_lookup[atoi(strtok(arg_str, &t))];
//        dimensionality = atoi(strtok(NULL, &t));
//        seed = atoi(strtok(NULL, &t));
//        search_function = atoi(strtok(NULL, &t));
//
//    } else {
//
//        f = function_lookup[atoi(args[1])];
//        dimensionality = atoi(args[2]);
//        seed = atoi(args[3]);
//        search_function = atoi(args[4]);
//    }

    srand(time(nullptr));
    f = function_lookup[12];
    dimensionality = 20;
    seed = rand();
    search_function = 7;

    // Set up the search functions
    seedMT(seed);
    random_walk random_walk_search(f);
    local local_search(f);
    iterative_local iterative_local_search(f);
    differential_evolution differential_evolution_search(f);
    genetic_algorithm genetic_algorithm_search(f);
    particle_swarm particle_swarm_search(f);
    soma soma_search(f);
    firefly firefly_search(f);
    harmony harmony_search(f);

    // return the results of the search
    if (search_function == 0)
        std::cout << random_walk_search.search(1, dimensionality) << std::endl;
    else if (search_function == 1)
        std::cout << local_search.search(1, dimensionality) << std::endl;
    else if (search_function == 2)
        std::cout << iterative_local_search.search(1, dimensionality) << std::endl;
    else if (search_function == 3)
        std::cout << differential_evolution_search.search(1, dimensionality) << std::endl;
    else if (search_function == 4)
        std::cout << genetic_algorithm_search.search(1, dimensionality) << std::endl;
    else if (search_function == 5)
        std::cout << particle_swarm_search.search(1, dimensionality) << std::endl;
    else if (search_function == 6)
        std::cout << soma_search.search(1, dimensionality) << std::endl;
    else if (search_function == 7)
        std::cout << firefly_search.search(1, dimensionality) << std::endl;
    else if (search_function == 8)
        std::cout << harmony_search.search(1, dimensionality) << std::endl;



    return 0;
}
