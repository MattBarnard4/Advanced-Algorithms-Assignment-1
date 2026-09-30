#include "../src/shannon_entropy.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

static bool approximately_equal(double a, double b, double tolerance = 1e-9)
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

    {
        std::vector<double> original = {0.5, 0.3, 0.2};

        std::vector<double> first_stage = {0.8, 0.2};
        std::vector<double> second_stage = {0.625, 0.375};

        double direct = shannon_entropy(original);

        double grouped =
            shannon_entropy(first_stage)
            + 0.8 * shannon_entropy(second_stage);

        std::cout << "\nShannon grouping test\n";
        std::cout << "Direct  = " << direct << '\n';
        std::cout << "Grouped = " << grouped << '\n';
        std::cout << "Difference = "
                << std::abs(direct - grouped)
                << '\n';

        assert(approximately_equal(direct, grouped));
    }

    std::cout << "All Shannon entropy tests passed.\n";
}