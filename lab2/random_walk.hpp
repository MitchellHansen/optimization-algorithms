#pragma once
#include "search_function.h"
#include <algorithm>

class random_walk : public search_function {

public:
    random_walk(function f) : search_function(f) {

    }

    double search(int permutations, int dimensionality) {

        timer t;
        t.start();

        std::vector<double> r;
        for (int i = 0; i < permutations; i++){

            std::vector<double> dimension_vals;

            for (int i = 0; i < dimensionality; i++) {
                auto val = fmod(randomMT(), (func.upper_bound * 2)) + func.lower_bound;
                dimension_vals.push_back(fmod(randomMT(), (func.upper_bound * 2)) + func.lower_bound);
            }

            r.push_back(func.compute(dimension_vals));

        }

        t.end();

        std::sort(r.begin(), r.end(), std::less<double>());

        return r[0];

    }

};


