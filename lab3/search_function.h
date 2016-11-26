#pragma once

class search_function {

public:

    function func;

    search_function(function f) : func(f) {
    };

    virtual double search(int permutations, int dimensionality) = 0;

protected:

    std::vector<double> generate_solution(int dimensionality){

        std::vector<double> tmp;
        for (int i = 0; i < dimensionality; i++) {
            tmp.push_back(fmod(randomMT(), (func.upper_bound * 2)) + func.lower_bound);
        }
        return tmp;
    }

    std::vector<std::vector<double>> generate_population(int dimensionality, int population_count){

        std::vector<std::vector<double>> tmp;
        for (int i = 0; i < dimensionality; i++) {
            tmp.push_back(generate_solution(dimensionality));
        }
        return tmp;
    }

    double check_bounds(double input){
        if (input > func.upper_bound)
            return func.upper_bound;
        else if (input < func.lower_bound)
            return func.lower_bound;
        else
            return input;
    }




};
