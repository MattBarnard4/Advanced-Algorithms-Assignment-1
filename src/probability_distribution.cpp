#include <vector>
#include <cmath>
#include "probability_distribution.hpp"
bool approximately_equal(double a, double b, double tolerance = 1e-9)
{
    return std::abs(a - b) < tolerance;
}

bool is_valid_distribution(const std::vector<double>& probabilities){
    if (probabilities.empty()){
        return false;
    } 
    double prob_total = 0.0;
    for (int i = 0; i < probabilities.size(); i++){
        if (probabilities[i] < 0.0 || probabilities[i] > 1.0){
            return false;
        }
        prob_total += probabilities[i];
    
    }
    if (!approximately_equal(prob_total, 1.0)){
        return false;
    }
    return true;
}

double is_valid_alpha(const double& a){
    if (a < 0){
        return false;
    }
    return true;
}