#include "src/renyi_entropy.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

bool approximately_equal(double a, double b, double tolerance = 1e-9)
{
    return std::abs(a - b) < tolerance;
}
int main() {

    // random non-uniform case
    {
        std::vector<double> p = {0.5, 0.5};

        double result = renyi_entropy(p, 2);

        assert(approximately_equal(result, 0.0));
    }
}