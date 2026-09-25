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
