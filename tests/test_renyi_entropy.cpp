#include "../src/renyi_entropy.hpp"
#include "../src/shannon_entropy.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>
#include <iomanip>

static bool approximately_equal(double a, double b, double tolerance = 1e-9)
{
    return std::abs(a - b) < tolerance;
}

std::vector<double> make_joint_distribution(
    const std::vector<double>& p, const std::vector<double>& q) {
    std::vector<double> joint;

    for (double px : p){
        for (double py: q) {
            joint.push_back(px * py);
        }
    }
    return joint;
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

    {
        std::vector<double> p = {0.7, 0.2, 0.08, 0.02};

        std::vector<double> alphas = {
            0.9,
            0.99,
            0.999,
            0.999999,
            0.99999999,
            1.00000001,
            1.000001,
            1.001,
            1.01,
            1.1
        };

        double shannon = shannon_entropy(p);

        std::cout << std::setprecision(15);

        std::cout << "\nShannon entropy: " << shannon << "\n\n";

        for (double alpha : alphas) {
            double renyi = renyi_entropy(p, alpha);
            double difference = std::abs(renyi - shannon);

            std::cout
                << "alpha = " << alpha
                << " | Renyi = " << renyi
                << " | difference = " << difference
                << '\n';
        }
    }
    {
        std::vector<double> p = {0.7, 0.2, 0.08, 0.02};

        double shannon = shannon_entropy(p);

        std::vector<double> alphas = {
            1.0 - 1e-8,
            1.0 - 1e-10,
            1.0 - 1e-12,

            1.0 + 1e-8,
            1.0 + 1e-10,
            1.0 + 1e-12
        };

        std::cout << std::setprecision(17);

        std::cout << "\nTesting very close to alpha = 1\n";
        std::cout << "Shannon entropy = " << shannon << "\n\n";

        for (double alpha : alphas) {
            double renyi = renyi_entropy(p, alpha);
            double difference = std::abs(renyi - shannon);

            std::cout
                << "alpha = " << alpha
                << " | Renyi = " << renyi
                << " | difference = " << difference
                << '\n';
        }
    }

    std::cout << "All Renyi entropy tests passed.\n";

    {
        std::vector<double> p = {0.5, 0.5};
        std::vector<double> q = {0.75, 0.25};

        std::vector<double> joint = make_joint_distribution(p, q);

        double separate =
            shannon_entropy(p) + shannon_entropy(q);

        double combined =
            shannon_entropy(joint);

        std::cout << "\nShannon additivity\n";
        std::cout << "H(X) + H(Y) = " << separate << '\n';
        std::cout << "H(X,Y)      = " << combined << '\n';

        assert(approximately_equal(separate, combined));
    }

    {
        std::vector<double> p = {0.5, 0.5};
        std::vector<double> q = {0.75, 0.25};

        std::vector<double> joint = make_joint_distribution(p, q);

        std::vector<double> alphas = {
            0.0,
            0.5,
            1.0,
            2.0,
            5.0,
            10.0
        };

        std::cout << "\nRenyi additivity\n";

        for (double alpha : alphas) {

            double separate =
                renyi_entropy(p, alpha)
                + renyi_entropy(q, alpha);

            double combined =
                renyi_entropy(joint, alpha);

            std::cout
                << "alpha = " << alpha
                << " | separate = " << separate
                << " | joint = " << combined
                << " | difference = "
                << std::abs(separate - combined)
                << '\n';

            assert(approximately_equal(separate, combined));
        }
    }

    {
        std::vector<double> original = {0.5, 0.3, 0.2};

        std::vector<double> first_stage = {0.8, 0.2};
        std::vector<double> second_stage = {0.625, 0.375};

        std::vector<double> alphas = {
            0.0,
            0.5,
            1.0,
            2.0,
            5.0,
            10.0
        };

        std::cout << "\nRenyi grouping comparison\n";

        for (double alpha : alphas) {

            double direct =
                renyi_entropy(original, alpha);

            double grouped =
                renyi_entropy(first_stage, alpha)
                + 0.8 * renyi_entropy(second_stage, alpha);

            std::cout
                << "alpha = " << alpha
                << " | direct = " << direct
                << " | grouped = " << grouped
                << " | difference = "
                << std::abs(direct - grouped)
                << '\n';
        }
    }

    return 0;
}