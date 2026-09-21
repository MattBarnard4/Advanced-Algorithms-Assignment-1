#include <vector>
#include <cmath>

int shannon_entropy(const std::vector<double>& vector ){
    double total = 0;

    for(int i = 0; i < vector.size(); i++){
        total += (vector[i] * std::log2(-(vector[i])));
    }

    return total;
}