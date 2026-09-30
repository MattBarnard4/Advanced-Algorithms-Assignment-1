#include "../src/renyi_entropy.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

static bool approximately_equal(double a, double b, double tolerance = 1e-9)
{
    return std::abs(a - b) < tolerance;
}
int main() {

    // random non-uniform case
    {
        std::vector<double> p = {0.5, 0.5};

        double result = renyi_entropy(p, 2);

        assert(approximately_equal(result, 1.0));
    }
    {
        std::vector<double> p = {0.5, 0.5};

        double result = renyi_entropy(p, 2.0);

        assert(approximately_equal(result, 1.0));
    }


    // --------------------------------------------------
    // 2. Alpha = 0 special case
    // H_0 = log2(number of non-zero probabilities)
    // --------------------------------------------------
    {
        std::vector<double> p = {0.7, 0.2, 0.1, 0.0};

        double result = renyi_entropy(p, 0.0);

        assert(approximately_equal(result, std::log2(3.0)));
    }


    // --------------------------------------------------
    // 3. Alpha = 1 should equal Shannon entropy
    // --------------------------------------------------
    {
        std::vector<double> p = {0.5, 0.25, 0.25};

        double result = renyi_entropy(p, 1.0);

        assert(approximately_equal(result, 1.5));
    }


    // --------------------------------------------------
    // 4. Uniform distribution should have the same
    // entropy for every Renyi order
    // --------------------------------------------------
    {
        std::vector<double> p = {0.5, 0.5};

        assert(approximately_equal(renyi_entropy(p, 0.0), 1.0));
        assert(approximately_equal(renyi_entropy(p, 0.5), 1.0));
        assert(approximately_equal(renyi_entropy(p, 1.0), 1.0));
        assert(approximately_equal(renyi_entropy(p, 2.0), 1.0));
        assert(approximately_equal(renyi_entropy(p, 10.0), 1.0));
    }


    // --------------------------------------------------
    // 5. Uniform four-outcome distribution
    // H_alpha = log2(4) = 2 for all orders
    // --------------------------------------------------
    {
        std::vector<double> p = {0.25, 0.25, 0.25, 0.25};

        assert(approximately_equal(renyi_entropy(p, 0.0), 2.0));
        assert(approximately_equal(renyi_entropy(p, 0.5), 2.0));
        assert(approximately_equal(renyi_entropy(p, 1.0), 2.0));
        assert(approximately_equal(renyi_entropy(p, 2.0), 2.0));
        assert(approximately_equal(renyi_entropy(p, 10.0), 2.0));
    }


    // --------------------------------------------------
    // 6. Permutation invariance
    // Changing outcome labels/order should not change entropy
    // --------------------------------------------------
    {
        std::vector<double> p1 = {0.5, 0.3, 0.2};
        std::vector<double> p2 = {0.2, 0.5, 0.3};

        double h1 = renyi_entropy(p1, 2.0);
        double h2 = renyi_entropy(p2, 2.0);

        assert(approximately_equal(h1, h2));
    }


    // --------------------------------------------------
    // 7. Non-negativity
    // --------------------------------------------------
    {
        std::vector<double> p = {0.7, 0.2, 0.08, 0.02};

        std::vector<double> alphas = {0.0, 0.5, 1.0, 2.0, 5.0, 10.0};

        for (double alpha : alphas) {
            assert(renyi_entropy(p, alpha) >= 0.0);
        }
    }


    // --------------------------------------------------
    // 8. Renyi entropy decreases as alpha increases
    // for this non-uniform distribution
    // --------------------------------------------------
    {
        std::vector<double> p = {0.7, 0.2, 0.08, 0.02};

        double h0   = renyi_entropy(p, 0.0);
        double h05  = renyi_entropy(p, 0.5);
        double h1   = renyi_entropy(p, 1.0);
        double h2   = renyi_entropy(p, 2.0);
        double h5   = renyi_entropy(p, 5.0);
        double h10  = renyi_entropy(p, 10.0);

        assert(h0 >= h05);
        assert(h05 >= h1);
        assert(h1 >= h2);
        assert(h2 >= h5);
        assert(h5 >= h10);
    }


    // --------------------------------------------------
    // 9. Invalid probability distribution should throw
    // --------------------------------------------------
    {
        std::vector<double> p = {0.7, 0.7};

        bool threw_exception = false;

        try {
            renyi_entropy(p, 2.0);
        }
        catch (const std::invalid_argument&) {
            threw_exception = true;
        }

        assert(threw_exception);
    }


    // --------------------------------------------------
    // 10. Negative alpha should throw
    // --------------------------------------------------
    {
        std::vector<double> p = {0.5, 0.5};

        bool threw_exception = false;

        try {
            renyi_entropy(p, -1.0);
        }
        catch (const std::invalid_argument&) {
            threw_exception = true;
        }

        assert(threw_exception);
    }


    std::cout << "All Renyi entropy tests passed.\n";

    return 0;
}