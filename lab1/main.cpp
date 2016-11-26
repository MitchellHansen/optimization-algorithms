#define _USE_MATH_DEFINES
#include <cmath>  
#include <iostream>
#include <vector>
#include <map>
#include <chrono>
#include "mtrand.h"
#include <algorithm>


std::vector<double> c = {0.806,0.517,0.1,0.908,0.965,0.669,0.524,0.902,0.351,0.876,0.462,
   0.491,0.463,0.741,0.352,0.869,0.813,0.811,0.0828,0.964,0.789,0.360,0.369,
   0.992,0.332,0.817,0.632,0.883,0.608,0.326};

double a[][10] =
       {
            {9.681,0.667,4.783,9.095,3.517,9.325,6.544,0.211,5.122,2.02},
            {9.4,2.041,3.788,7.931,2.882,2.672,3.568,1.284,7.033,7.374},
            {8.025,9.152,5.114,7.621,4.564,4.711,2.996,6.126,0.734,4.982},
            {2.196,0.415,5.649,6.979,9.510,9.166,6.304,6.054,9.377,1.426},
            {8.074,8.777,3.467,1.863,6.708,6.349,4.534,0.276,7.633,1.567},
            {7.650,5.658,0.720,2.764,3.278,5.283,7.474,6.274,1.409,8.208},
            {1.256,3.605,8.623,6.905,4.584,8.133,6.071,6.888,4.187,5.448},
            {8.314,2.261,4.24,1.781,4.124,0.932,8.129,8.658,1.208,5.762},
            {0.226,8.858,1.42,0.954,1.622,4.698,6.228,9.096,0.972,7.637},
            {7.305,2.228,1.242,5.928,9.133,1.826,4.06,5.204,8.713,8.247},
            {0.652,7.027,0.508,4.876,8.807,4.632,5.808,6.937,3.291,7.016},
            {2.699,3.516,5.847,4.119,4.461,7.496,8.817,0.69,6.593,9.789},
            {8.327,3.897,2.017,9.57,9.825,1.15,1.395,3.885,6.354,0.109},
            {2.132,7.006,7.136,2.641,1.882,5.943,7.273,7.691,2.88,0.564},
            {4.707,5.579,4.08,0.581,9.698,8.542,8.077,8.515,9.231,4.67},
            {8.304,7.559,8.567,0.322,7.128,8.392,1.472,8.524,2.277,7.826},
            {8.632,4.409,4.832,5.768,7.05,6.715,1.711,4.323,4.405,4.591},
            {4.887,9.112,0.17,8.967,9.693,9.867,7.508,7.77,8.382,6.74},
            {2.44,6.686,4.299,1.007,7.008,1.427,9.398,8.48,9.95,1.675},
            {6.306,8.583,6.084,1.138,4.350,3.134,7.853,6.061,7.457,2.258},
            {0.652,2.343,1.37,0.821,1.31,1.063,0.689,8.819,8.833,9.07},
            {5.558,1.272,5.756,9.857,2.279,2.764,1.284,1.677,1.244,1.234},
            {3.352,7.549,9.817,9.437,8.687,4.167,2.57,6.54,0.228,0.027},
            {8.798,0.88,2.37,0.168,1.701,3.68,1.231,2.39,2.499,0.064},
            {1.46,8.057,1.337,7.217,7.914,3.615,9.981,9.198,5.292,1.224},
            {0.432,8.645,8.774,0.249,8.081,7.461,4.416,0.652,4.002,4.644},
            {0.679,2.8,5.523,3.049,2.968,7.225,6.73,4.199,9.614,9.229},
            {4.263,1.074,7.286,5.599,8.291,5.2,9.214,8.272,4.398,4.506},
            {9.496,4.83,3.15,8.27,5.079,1.231,5.731,9.494,1.883,9.732},
            {4.138,2.562,2.532,9.661,5.611,5.5,6.886,2.341,9.699,6.5}
        };

double schwefel(std::vector<double> input){

    int upper_bound = 512;
    int lower_bound = -512;

    double sum = 0;

    for (int i = 0; i < input.size(); i++){
        sum += (-input[i]) * std::sin(std::sqrt(std::abs(input[i])));
    }

    return sum;
}


double first_de_jong(std::vector<double> input){

    int upper_bound = 100;
    int lower_bound = -100;

    double sum = 0;

    for (int i = 0; i < input.size(); i++){
        sum += std::pow(input[i], 2);
    }

    return sum;
}

double rosenbrock(std::vector<double> input){

    int upper_bound = 100;
    int lower_bound = -100;

    double sum = 0;

    for (int i = 0; i < input.size() - 1; i++){
        sum += 100 * std::pow((std::pow(input[i], 2) - input[i + 1]), 2) + std::pow((1 - input[i]), 2);
    }

    return sum;

}

double rastrigin(std::vector<double> input){

    int upper_bound = 30;
    int lower_bound = -30;

    double sum = 0;

    for (int i = 0; i < input.size(); i++){
        sum += std::pow(input[i], 2) - 10 * std::cos(2 * M_PI * input[i]);
    }

    sum *= 2 * input.size();

    return sum;

}

double griewangk(std::vector<double> input){

    int upper_bound = 500;
    int lower_bound = -500;

    double sum = 0;

    for (int i = 0; i < input.size(); i++){
        sum += std::pow(input[i], 2) / 4000;
    }

    double product = 0;

    for (int i = 0; i < input.size(); i++){
        product *= std::cos(input[i] / sqrt(i + 1));
    }

    return 1 + sum - product;

}


double sine_envelope_sine_wave(std::vector<double> input){

    int upper_bound = 30;
    int lower_bound = -30;

    double sum = 0;

    for (int i = 0; i < input.size() - 1; i++){
        sum += 0.5 + (std::pow(std::sin(std::pow(input[i], 2) + std::pow(input[i + 1], 2) - 0.5), 2)) /
                (1 + 0.001 * (std::pow(input[i], 2) + std::pow(input[i + 1], 2)));
    }

    return sum;
}

double stretched_v_sine_wave(std::vector<double> input){

    int upper_bound = 30;
    int lower_bound = -30;

    double sum = 0;

    for (int i = 0; i < input.size() - 1; i++){
        sum += std::pow(std::pow(input[i], 2) + std::pow(input[i + 1], 2), 1.0 / 4) *
                std::pow(std::sin(50 * std::pow(std::pow(input[i], 2) + std::pow(input[i + 1], 2), 1.0 / 10)), 2) + 1;
    }

    return sum;

}


double ackleys_one(std::vector<double> input){

    int upper_bound = 32;
    int lower_bound = -32;

    double sum = 0;

    for (int i = 0; i < input.size() - 1; i++){
        sum += (1.0 / pow(M_E, 0.2)) *
                std::sqrt(std::pow(input[i], 2) + std::pow(input[i + 1], 2)) +
                3 * std::cos(2 * input[i]) +
                std::sin(2 * input[i + 1]);
    }

    return sum;

}


double ackleys_two(std::vector<double> input){

    int upper_bound = 32;
    int lower_bound = -32;

    double sum = 0;

    for (int i = 0; i < input.size() - 1; i++){
        sum += 20 + M_E -
               (20 / (std::pow(M_E, 0.2) * std::sqrt(((std::pow(input[i], 2) + std::pow(input[i+1], 2) + 1) / 2)))) -
               std::pow(M_E, 0.5 * std::cos(2 * M_PI * input[i]) + cos(2 * M_PI * input[i + 1]));
    }

    return sum;
}



double egg_holder(std::vector<double> input){

    int upper_bound = 500;
    int lower_bound = -500;

    double sum = 0;

    for (int i = 0; i < input.size() - 1; i++) {
        sum += -input[i] * std::sin(std::sqrt(abs(input[i] - input[i + 1] - 47))) -
                (input[i + 1] + 47) * std::sin(std::sqrt(std::abs(input[i + 1] + 47 + input[i] / 2)));
    }

    return sum;
}

double rana(std::vector<double> input){

    int upper_bound = 500;
    int lower_bound = -500;

    double sum = 0;

    for (int i = 0; i < input.size() - 1; i++) {
        sum += input[i] * std::sin(std::sqrt(std::abs(input[i + 1] - input[i] + 1))) *
                                   std::cos(std::sqrt(std::abs(input[i + 1] + input[i] + 1))) +
               (input[i + 1] + 1) *
                                   std::cos(std::sqrt(std::abs(input[i + 1] - input[i] + 1))) *
                                   std::sin(std::sqrt(std::abs(input[i + 1] + input[i] + 1)));
    }

    return sum;
}


double pathological(std::vector<double> input){

    int upper_bound = 100;
    int lower_bound = -100;

    double sum = 0;

    for (int i = 0; i < input.size() - 1; i++) {
        sum += 0.5 +
               (std::pow(std::sin(std::sqrt(100 * std::pow(input[i], 2) + std::pow(input[i + 1], 2))), 2) - 0.5) /
               (1 + 0.001 * std::pow(std::pow(input[i], 2) - 2 * input[i] * input[i + 1] + std::pow(input[i + 1], 2), 2));
    }

    return sum;
}

double michalewicz(std::vector<double> input){

    int upper_bound = M_PI;
    int lower_bound = 0;

    double sum = 0;

    for (int i = 0; i < input.size() - 1; i++) {
        sum += std::sin(input[i]) * std::pow(std::sin(i * std::pow(input[i], 2) / M_PI), 20);
    }

    return -sum;
}


double masters_cosine_wave(std::vector<double> input){

    int upper_bound = 30;
    int lower_bound = -30;

    double sum = 0;

    for (int i = 0; i < input.size() - 1; i++) {
        sum += std::pow(M_E, -(1/8) * (std::pow(input[i], 2) + std::pow(input[i + 1], 2) + 0.5 * input[i + 1] * input[i])) *
               std::cos(4 * std::sqrt(std::pow(input[i], 2) + std::pow(input[i + 1], 2) + 0.5 * input[i] * input[i + 1]));
    }
    return -sum;
}

double shekels_foxholes(std::vector<double> input){

    int upper_bound = 10;
    int lower_bound = 0;

    double sum = 0;

    for (int i = 0; i < c.size() - 1; i++) {

        double bottom_sum = 0;

        for (int q = 0; q < input.size(); q++){
            bottom_sum = std::pow(input.at(q) - a[i][q], 2);
        }

        sum += 1 / (bottom_sum + c[i]);
    }

    return -sum;
}

struct timer{
    std::chrono::high_resolution_clock::time_point t1;
    std::chrono::high_resolution_clock::time_point t2;
    void start(){t1 = std::chrono::high_resolution_clock::now();}
    void end(){t2 = std::chrono::high_resolution_clock::now();}
    double duration(){ return std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();}
};


double set_within(double val, double prior_upper, double prior_lower, double after_upper, double after_lower){
    return ((after_upper - after_lower) * (val - prior_lower) / (prior_upper - prior_lower)) + after_lower;
}

struct function{

    double (*function_pointer)(std::vector<double>);
    double range = 0;
    double upper_bound = 0;
    double lower_bound = 0;

    timer t;

    function(double (*func)(std::vector<double>), double upper_bound, double lower_bound){
        function_pointer = func;
        this->upper_bound = upper_bound;
        this->lower_bound = lower_bound;
    }

    double compute_defined(std::vector<double> input){

        for (auto v: input) {
            if (v >= lower_bound && v <= upper_bound) {
                return function_pointer(input);
            } else {
                return 0;
            }

        }
    };


    enum Test_Data { MEAN, MEDIAN, DEVIATION, AVG_TIME, DIMENSIONALIY, UPPER_RANGE, LOWER_RANGE};

    std::map<Test_Data, double> run_tests_random(int dimensionality, int permutations){

        std::vector<double> times;
        std::vector<double> vals;

        for (int i = 0; i < permutations; i++) {

            std::vector<double> dimension_vals;

            for (int i = 0; i < dimensionality; i++){
                dimension_vals.push_back(fmod(std::rand() , (upper_bound * 2)) + lower_bound);
            }

            t.start();

            vals.push_back(compute_defined(dimension_vals));

            t.end();

            times.push_back(t.duration());
        }

        // Mean
        double mean = 0;
        for (double v: vals){
            mean += v;
        }
        mean /= vals.size();

        // Median
        double median = vals[std::floor(vals.size() / 2)];

        // Standard Deviation
        double sum = 0;
        for (double v: vals){
            sum += std::pow(v - mean, 2);
        }
        double deviation = std::sqrt(sum / vals.size());

        // Time Mean
        double time_mean = 0;
        for (double v: times){
            time_mean += v;
        }
        time_mean /= times.size();

        // Range
        std::sort(vals.begin(), vals.end());

        double lower_range = vals.front();
        double upper_range = vals.back();

        std::map<Test_Data, double> ret;

        ret[Test_Data::DIMENSIONALIY] = dimensionality;
        ret[Test_Data::AVG_TIME] = time_mean;
        ret[Test_Data::DEVIATION] = deviation;
        ret[Test_Data::MEAN] = mean;
        ret[Test_Data::MEDIAN] = median;
        ret[Test_Data::UPPER_RANGE] = upper_range;
        ret[Test_Data::LOWER_RANGE] = lower_range;

        std::cout << " & " << dimensionality << " & " << mean << " & " << median << " & " << deviation << " & " << time_mean << " \\\\ \\hline" << std::endl;

        return ret;
    };

    std::map<Test_Data, double> run_tests_defined(std::vector<double> input, int permutations){

        std::vector<double> times;
        std::vector<double> vals;

        for (int i = 0; i < permutations; i++) {

            t.start();

            vals.push_back(function_pointer(input));

            t.end();

            times.push_back(t.duration());
        }

        // Mean
        double mean = 0;
        for (double v: vals){
            mean += v;
        }
        mean /= vals.size();

        // Median
        double median = vals[std::floor(vals.size() / 2)];

        // Standard Deviation
        double sum = 0;
        for (double v: vals){
            sum += std::pow(v - mean, 2);
        }
        double deviation = std::sqrt(sum / vals.size());

        // Time Mean
        double time_mean = 0;
        for (double v: times){
            time_mean += v;
        }
        time_mean /= times.size();

        // Range
        std::sort(vals.begin(), vals.end());

        double lower_range = vals.front();
        double upper_range = vals.back();

        std::map<Test_Data, double> ret;

        ret[Test_Data::DIMENSIONALIY] = input.size();
        ret[Test_Data::AVG_TIME] = time_mean;
        ret[Test_Data::DEVIATION] = deviation;
        ret[Test_Data::MEAN] = mean;
        ret[Test_Data::MEDIAN] = median;
        ret[Test_Data::UPPER_RANGE] = upper_range;
        ret[Test_Data::LOWER_RANGE] = lower_range;

        return ret;

    };

};

int main() {

    MTRand r(time(NULL));
    std::cout << r();


    srand(time(NULL));

    function schwefel_f(&schwefel, 512, -512);
    function de_jong_f(&first_de_jong, 100, -100);
    function rosenbrock_f(&rosenbrock, 100, -100);
    function rastrigin_f(&rastrigin, 30, -30);
    function griegwangk_f(&griewangk, 500, -500);
    function sine_envelope_sine_wave_f(&sine_envelope_sine_wave, 30, -30);
    function stretched_v_sine_wave_f(&stretched_v_sine_wave, 30, -30);
    function ackleys_one_f(&ackleys_one, 32, -32);
    function ackleys_two_f(&ackleys_two, 32, -32);
    function egg_holder_f(&egg_holder, 500, -500);
    function rana_f(&rana, 500, -500);
    function pathological_f(&pathological, 100, -100);
    function michalewicz_f(&michalewicz, M_PI, 0);
    function masters_cosine_wave_f(&masters_cosine_wave, 30, -30);
    function shekels_foxholes_f(&shekels_foxholes, 10, 0);


    std::string vals[] {
        "MEAN", "MEDIAN", "DEVIATION", "AVG_TIME", "DIMENSIONALIY", "UPPER_RANGE", "LOWER_RANGE"
    };

    int permutations = 10000;

    for (int i = 10; i < 40; i += 10) {

        auto ret = schwefel_f.run_tests_random(i, permutations);
        ret = de_jong_f.run_tests_random(i, permutations);
        ret = rosenbrock_f.run_tests_random(i, permutations);
        ret = rastrigin_f.run_tests_random(i, permutations);
        ret = griegwangk_f.run_tests_random(i, permutations);
        ret = sine_envelope_sine_wave_f.run_tests_random(i, permutations);
        ret = stretched_v_sine_wave_f.run_tests_random(i, permutations);
        ret = ackleys_one_f.run_tests_random(i, permutations);
        ret = ackleys_two_f.run_tests_random(i, permutations);
        ret = egg_holder_f.run_tests_random(i, permutations);
        ret = rana_f.run_tests_random(i, permutations);
        ret = pathological_f.run_tests_random(i, permutations);
        ret = michalewicz_f.run_tests_random(i, permutations);
        ret = masters_cosine_wave_f.run_tests_random(i, permutations);
        ret = shekels_foxholes_f.run_tests_random(i, permutations);
    }

    return 0;
}
