My initial understanding of Shannon entropy

Shannon entropy is average uncertainty in a set of possible outcomes or in a probability distribution, denoted by the formula: $$H(X) = - \sum_{i=1}^{n} P(x_i) \log_b P(x_i)$$ 
Shannon information is not semantic meaning; it is the information in the sense of uncertainity about which possible outcome will occur.

Shannon derived this formula by first listing three requirements he thought should be satisfied in order to answer the question he posed of what is the best way of measuring uncertainty of certain possible outcomes. His theorem isnt neccessary for the theory; it mainly matches the definition plausible. The real justification comes from what the definition allows us to derive. This also makes me question whether those requirements were chosen becase Shannon considered them reasonable, and whether there is other better requirements or the legitimacy of his requirements.

Renyi then introduces a generalised extension of Shannon entropy providing us with a spectrum of entropy measures that quantify the diversity or uncertainty of a system based on a paramater a (alpha). Renyi measurements only mean something when probability distribution is uneven. Maybe I could implement Renyi entropy aswell to gain a deeper understanding of Shannon entropy or other further extensions of it to analyse the correctness of Shannon's work.

A more refined question I may frame my implementation around: "I want to understand why Shannon entropy is mathematically justified under Shannon’s chosen requirements, verify that my implementation preserves its defining properties, and investigate what changes when those requirements are generalised.”


My initial implementation thoughts :
- receive a set of probabilities
- initialise entropy at 0
- look at each probability and calculate its contribution to the total entropy and add it.
- return the total entropy

input:
- vector of doubles

output:
- double 

entropy function:
- recieves the input
- initialise the entropy total
- loop through the vector and calculate each probabilities contribution and add it to the running total (-p * log base 2 * p)
- once loop is done return the entropy total

edge cases:
- normally log(0) isnt defined even though a probability of 0 does work in the entropy calculation due to 0log0=0 so ill have to write an edge case maybe at the start at the for loop if i = 0...
- I wont initially care about validation and assume my inputs are real probability distributions and do that in the next stage.

- Ive completed my initial implementation and created a edge case for probability of 0, now I need to do input validity and invariants

Possible correctness ideas for track C:
    - Input condition: before the calculation starts, probabilities represents a valid probability distribution.
    - Loop invariant: during the calculation, total always equals the entropy contribution of exactly the probabilities       processed so far.

## initial Renyi testing

Ive now tested the Renyi implementation at alpha = 0, 1 and 2 to verify every part of the function.

For alpha = 0, the implementation correctly calculated entropy from
the number of non-zero probabilities.

For alpha = 1, the function returned the Shannon entropy implementation,
which is consistent with Shannon entropy being the limiting case of
Renyi entropy as alpha approaches 1.

For uniform probability distributions, changing alpha did not change
the entropy. For example, (0.5, 0.5) produced 1 bit for alpha values
0, 0.5, 1, 2 and 10. This agrees with the theoretical property that
all Renyi orders equal log2(n) for a uniform distribution.

For the non-unirform distribution (0.7, 0.2, 0.08, 0.02), entropy decreased as alpha increased.

Results:

alpha = 0,  2.0000
alpha = 0.5, 1.5448
alpha = 1, 1.2290
alpha = 2, 0.8975
alpha = 5, 0.6425
alpha = 10, 0.5717

This helped backup that Renyi's parameter matters. The underlying probability distribution did not change, but increasing alpha placed greater importance on the high probability outcomes. lower alpha values gave relatively more importance to the rare outcomes. This helps to the questioning of that uncertainty is not neccessarily represented by one universal value unless the properties and interpretation of the entropy measure are specified.

Renyi invariant

reordering the probabilities produced the same entropy, which is expected because entropy should depend on the probability values and not on the ordering of outcomes.

As I examine these results I now want to investigate my finding further by comparing the shannon entropy of a distribution to the reny entropy of that same distribution with a range of alphas that resemble as a -> 1.

Results from above: 

Shannon entropy: 1.22897245893578

alpha = 0.9 | Renyi = 1.28165957456763 | difference = 0.0526871156318538
alpha = 0.99 | Renyi = 1.23402943484138 | difference = 0.00505697590560183
alpha = 0.999 | Renyi = 1.22947609391399 | difference = 0.00050363497821504
alpha = 0.999999 | Renyi = 1.22897296237605 | difference = 5.03440272137112e-07
alpha = 0.99999999 | Renyi = 1.22897246313587 | difference = 4.20009538260047e-09
alpha = 1.00000001 | Renyi = 1.22897245521505 | difference = 3.72072439525084e-09
alpha = 1.000001 | Renyi = 1.22897195554659 | difference = 5.03389189665526e-07
alpha = 1.001 | Renyi = 1.22846928095554 | difference = 0.000503177980237579
alpha = 1.01 | Renyi = 1.22396118280133 | difference = 0.00501127613444385
alpha = 1.1 | Renyi = 1.18085486635685 | difference = 0.0481175925789212

this demonstrates as alpha approaches 1 its closer to normal shannon entropy and the further away the alpha from 1 the bigger the difference. next ill do even closer to 1 to push it harder.


Testing very close to alpha = 1
Shannon entropy = 1.2289724589357756

alpha = 0.99999998999999995 | Renyi = 1.2289724631358709 | difference = 4.2000953826004661e-09
alpha = 0.99999999989999999 | Renyi = 1.2289720524651173 | difference = 4.0647065824295225e-07
alpha = 0.99999999999900002 | Renyi = 1.228861591395072 | difference = 0.00011086754070355198
alpha = 1.0000000099999999 | Renyi = 1.2289724552150512 | difference = 3.7207243952508406e-09
alpha = 1.0000000001 | Renyi = 1.2289736542829279 | difference = 1.1953471523717951e-06
alpha = 1.0000000000010001 | Renyi = 1.2290454866548202 | difference = 7.3027719044604922e-05

This is my best finding so far as the results are starting to deteriorate. mathematically id expect that as i get even closer to one it would be closer to normal shannon entropy where a = 1 but as i get extremly close the numerical error gets larger. This suggests that the direct formula becomes numerically unstable near alpha=1, despite the mathematical limit being well-defined as Shannon entropy.

By comparing the different Renyi orders, properities of Shannon entropy that I have further investigated like permutation invariance and maximum entropy for a uniform distribution, also exist in the wider Renyi family, which suggests that these properties alone do not fully explain what makes Shannon entropy distinct.

With this and the a -> 1 experiment, I can now further investigate which mathematical properties actually distinguish Shannon entropy from other Renyi orders, and also how an implementation can preserve the mathematical definition of Shannon entropy while remaining numerically reliable, linking the correctness of the mathematics to the correctness of the implementation.

Next ill do tests on additivity for Shannon and Renyi and see if Shannons results uniquely distinguish it or if both entropys results are the same/similar. I do expect them to be the same the math for both satisfies the same argument that H(X, Y) = H(X) + H(Y) and Ha(X, Y) = Ha(X) + Ha(Y) (renyi), but it will show another property of shannon entropy that doesnt make it unique.

