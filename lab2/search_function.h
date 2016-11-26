#pragma once

class search_function {

public:
    function func;

    search_function(function f) : func(f) {
    };

    virtual double search(int permutations, int dimensionality) = 0;

};
