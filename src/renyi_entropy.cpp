#include <vector>
#include <cmath>
#include "renyi_entropy.hpp"
#include <stdexcept>

double renyi_entropy(const std::vector<double>& probabilities, double alpha){
    double power_sum = 0;

    for (int i = 0; i < probabilities.size(); i++){
        power_sum += std::pow(probabilities[i], alpha);

    }
    power_sum = std::log2(power_sum) / (1 - alpha);
    return power_sum;
}