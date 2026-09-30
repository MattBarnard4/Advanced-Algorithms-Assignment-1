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

Shannon additivity
H(X) + H(Y) = 1.8112781244591329
H(X,Y)      = 1.8112781244591329

next Renyi

Renyi additivity
alpha = 0 | separate = 2 | joint = 2 | difference = 0
alpha = 0.5 | separate = 1.8999686269529918 | joint = 1.8999686269529914 | difference = 4.4408920985006262e-16
alpha = 1 | separate = 1.8112781244591329 | joint = 1.8112781244591329 | difference = 0
alpha = 2 | separate = 1.6780719051126378 | joint = 1.6780719051126376 | difference = 2.2204460492503131e-16
alpha = 5 | separate = 1.5173156656092783 | joint = 1.5173156656092783 | difference = 0
alpha = 10 | separate = 1.4611500623142353 | joint = 1.4611500623142353 | difference = 0

These results confirm that additiviy for independent distributions is preserved for both Shannon entropy and the tested Renyi orders. the tiny differencees for some orders are consistent with the floating point rounding rather than a additivity failure. This agrees with my statement that additivity does not uniquely distinguish Shannon entropy either.

The last property ill test is grouping and recursivity. Shannon's grouping/recursivity idea says that making a choice all at once should give the same uncertainty as making it in stages. So ill do similar tests to compare Shannon and Renyi for this idea.

Shannon grouping test
Direct  = 1.48548
Grouped = 1.48548
Difference = 0

Renyi grouping comparison
alpha = 0 | direct = 1.5849625007211561 | grouped = 1.8 | difference = 0.21503749927884397
alpha = 0.5 | direct = 1.5345348591995369 | grouped = 1.6295252477406166 | difference = 0.094990388541079662
alpha = 1 | direct = 1.4854752972273344 | grouped = 1.4854752972273344 | difference = 0
alpha = 2 | direct = 1.3959286763311392 | grouped = 1.2864230755241133 | difference = 0.10950560080702587
alpha = 5 | direct = 1.219580360852937 | grouped = 1.0585227853977215 | difference = 0.16105757545521548
alpha = 10 | direct = 1.110128053562691 | grouped = 0.95965523199475755 | difference = 0.1504728215679334

These results confirmed that my Shannon implementation preserves the recursive grouping behaviour used in Shannon's axiomatic characterisation. I then applied the same grouping equation to Renyi entropy at several orders. The equality held at alpha = 1 which corresponds to shannon entropy, but generally failed for other orders. the grouping experiment therefore provides a clearer explanation of what distinguishes shannon entropy: Shannon's ordinary probability weighted recursive grouping rule is satisfied at alpha = 1, but is generally not preserved by Renyi entropy for alpha not equal to 1.

I'm now happy with the mathematical correctness side of my investigation and want to go back to my alpha -> 1 limit testing for the implementational correctness side of my investigation. Ill do this by implementing a more numerically stable version and show the difference from the hopefully improved version against my initial naive Renyi entropy.

implemented a stable version of the Renyi entropy implementation that should fix the numerical instability i ran into originally.

These are the rsults of the same tests that I run for alpha -> 1 comparing normal Renyi versus stable Renyi implementation

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
alpha = 0.9 | Stable Renyi = 1.28165957456763 | difference = 0.0526871156318542
alpha = 0.99 | Stable Renyi = 1.23402943484138 | difference = 0.00505697590560472
alpha = 0.999 | Stable Renyi = 1.22947609391423 | difference = 0.000503634978449519
alpha = 0.999999 | Stable Renyi = 1.22897296234242 | difference = 5.03406646368276e-07
alpha = 0.99999999 | Stable Renyi = 1.22897246396984 | difference = 5.03406472063261e-09
alpha = 1.00000001 | Stable Renyi = 1.22897245390171 | difference = 5.0340640544988e-09
alpha = 1.000001 | Stable Renyi = 1.22897195552959 | difference = 5.03406188734346e-07
alpha = 1.001 | Stable Renyi = 1.22846928095548 | difference = 0.000503177980298419
alpha = 1.01 | Stable Renyi = 1.22396118280132 | difference = 0.00501127613445629
alpha = 1.1 | Stable Renyi = 1.18085486635685 | difference = 0.0481175925789215

Testing very close to alpha = 1
Shannon entropy = 1.2289724589357756

alpha = 0.99999998999999995 | Renyi = 1.2289724631358709 | difference = 4.2000953826004661e-09
alpha = 0.99999999989999999 | Renyi = 1.2289720524651173 | difference = 4.0647065824295225e-07
alpha = 0.99999999999900002 | Renyi = 1.228861591395072 | difference = 0.00011086754070355198
alpha = 1.0000000099999999 | Renyi = 1.2289724552150512 | difference = 3.7207243952508406e-09
alpha = 1.0000000001 | Renyi = 1.2289736542829279 | difference = 1.1953471523717951e-06
alpha = 1.0000000000010001 | Renyi = 1.2290454866548202 | difference = 7.3027719044604922e-05
alpha = 0.99999998999999995 | Stable Renyi = 1.2289724639698403 | difference = 5.0340647206326139e-09
alpha = 0.99999999989999999 | Stable Renyi = 1.2289724589861166 | difference = 5.0341064650183398e-11
alpha = 0.99999999999900002 | Stable Renyi = 1.2289724589362794 | difference = 5.0381920857489604e-13
alpha = 1.0000000099999999 | Stable Renyi = 1.2289724539017115 | difference = 5.0340640544987991e-09
alpha = 1.0000000001 | Stable Renyi = 1.2289724588854349 | difference = 5.0340620560973548e-11
alpha = 1.0000000000010001 | Stable Renyi = 1.2289724589352722 | difference = 5.0337511936504598e-13


from the results i can see that the stable implementation produced almost identical results to the original when the alpha was not extremely close to 1, however when it was extremely close there was more of a clear difference. . For example, at approximately 1-10^{-12}, the direct implementation differed from Shannon entropy by about 1.11 times 10^{-4}, whereas the stable implementation differed by only approximately 5.04 times 10^{-13}. Similarly, at approximately 1+10^{-12}, the direct implementation differed by about 7.30 times 10^{-5}, while the stable implementation differed by approximately 5.03 times 10^{-13}.

This confirms that the deterioration observed in the original implementation was caused by the numerical form of the calculation rather than a failure of the mathematical relationship between Renyi and Shannon entropy.

The stable implementation avoids much of the loss of precision by using exmp1 to accurately calculate values of the form e^x - 1 when x is small, and log1p to accurately calculate ln(1 + x) when x is close to zero.

An important observation from this is that the remaining difference between the stable Renyi value and Shannon entropy is not neccessarily numerical error. For any alpha not equal to 1, Renyi entropy is mathematically a slight different value from Shannon entropy. As a approaches 1, this difference should also approach zero. 

This experiment demonstrates an important distinction between mathematical correctness and computational correctness. Shannon entropy is mathematically the limiting case of Renyi entropy as alpha -> 1, but simply translating the Renyi formula directly into code did not preserve that relationship reliably under finite-precision arithmetic. Reformulating the calculation produced an implementation whose numerical behaviour much more closely followed the underlying mathematics.

This supported my goal of verifying that the mathematical properties defining Shannon entropy are actually preserved by the implementation, rather than assuming that a mathematically correct formula automatically produces a computationally reliable algorithm.

potential issue i could mention: at 10^{-8}, the naive version sometimes appears slightly closer to Shannon than the stable one. But that didnt mean the naive version was better there. Because when alpha doesnt equal 1, the exact Renyi value is supposed to differ slightly from Shannon; rounding error in the naive calculation can accidentally cancel some of that real difference.