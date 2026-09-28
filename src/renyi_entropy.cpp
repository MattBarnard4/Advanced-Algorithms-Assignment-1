#include <vector>
#include <cmath>
#include "renyi_entropy.hpp"
#include <stdexcept>
#include "probability_distribution.hpp"
double renyi_entropy(const std::vector<double>& probabilities, double alpha){
    if (!is_valid_distribution(probabilities)){
        throw std::invalid_argument("Invalid probability distribution");
    }
    if (!is_valid_alpha(alpha)){
        throw std::invalid_argument("Invalid Alpha variable");
    }
    double power_sum = 0;

    for (int i = 0; i < probabilities.size(); i++){
        power_sum += std::pow(probabilities[i], alpha);

    }
    power_sum = std::log2(power_sum) / (1 - alpha);
    return power_sum;
}