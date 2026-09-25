#include <vector>
#include <cmath>
#include "shannon_entropy.hpp"

double shannon_entropy(const std::vector<double>& probabilities){
    double total = 0;

    for(int i = 0; i < probabilities.size(); i++){
        if (probabilities[i] == 0.0){
            continue;
        }
        total += -(probabilities[i] * std::log2((probabilities[i])));
    }

    return total;
}