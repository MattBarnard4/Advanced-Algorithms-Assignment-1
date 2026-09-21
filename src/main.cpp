#include "shannon_entropy.cpp"
#include <vector>
#include <iostream>
int main() {
    std::vector<double> vec = {0.5, 0.5};
    double shann_entropy = shannon_entropy(vec);
    std::cout << shann_entropy; 
}