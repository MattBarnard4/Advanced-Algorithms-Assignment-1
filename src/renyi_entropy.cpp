#include <vector>
#include <cmath>
#include "renyi_entropy.hpp"
#include <stdexcept>
#include "probability_distribution.hpp"
#include "shannon_entropy.hpp"
double renyi_entropy(const std::vector<double>& probabilities, double alpha){
    if (!is_valid_distribution(probabilities)){
        throw std::invalid_argument("Invalid probability distribution");
    }
    if (!is_valid_alpha(alpha)){
        throw std::invalid_argument("Invalid Alpha variable");
    }

    if (alpha == 1.0){
        return shannon_entropy(probabilities);
    }

    if (alpha == 0.0){
        int support_size = 0;

        for (double p : probabilities){
            if (p > 0.0){
                support_size++;
            }
        }

        return std::log2(support_size);
    }

    double power_sum = 0;

    for (int i = 0; i < probabilities.size(); i++){
        power_sum += std::pow(probabilities[i], alpha);

    }
    double entropy = std::log2(power_sum) / (1 - alpha);
    return entropy;
}