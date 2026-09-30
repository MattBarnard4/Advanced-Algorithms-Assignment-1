#pragma once
 
#include <vector>

double renyi_entropy(const std::vector<double>& probabilities, double alpha);

double renyi_entropy_stable(const std::vector<double>& probabilities, double alpha);