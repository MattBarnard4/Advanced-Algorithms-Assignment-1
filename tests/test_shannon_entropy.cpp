#include "src/shannon_entropy.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

bool approximately_equal(double a, double b, double tolerance = 1e-9)
{
    return std::abs(a - b) < tolerance;
}

int main()
{
    // Certain outcome -> zero entropy
    {
        std::vector<double> p = {1.0};

        double result = shannon_entropy(p);

        assert(approximately_equal(result, 0.0));
    }

    // Fair binary distribution -> 1 bit
    {
        std::vector<double> p = {0.5, 0.5};

        double result = shannon_entropy(p);

        assert(approximately_equal(result, 1.0));
    }

    // Uniform four-outcome distribution -> 2 bits
    {
        std::vector<double> p = {0.25, 0.25, 0.25, 0.25};

        double result = shannon_entropy(p);

        assert(approximately_equal(result, 2.0));
    }

    // Non-uniform distribution
    {
        std::vector<double> p = {0.5, 0.25, 0.25};

        double result = shannon_entropy(p);

        assert(approximately_equal(result, 1.5));
    }
    // Probability of 0 edge case
    {
        std::vector<double> p = {1.0, 0.0};
        double result = shannon_entropy(p);
        assert(approximately_equal(result, 0.0));
    }

    std::cout << "All Shannon entropy tests passed.\n";
}