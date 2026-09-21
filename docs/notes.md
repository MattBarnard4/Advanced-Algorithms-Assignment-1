My initial understanding of Shannon entropy

Shannon entropy is average uncertainty in a set of possible outcomes or in a probability distribution, denoted by the formula: $$H(X) = - \sum_{i=1}^{n} P(x_i) \log_b P(x_i)$$ 
Shannon information is not semantic meaning; it is the information in the sense of uncertainity about which possible outcome will occur.

Shannon derived this formula by first listing three requirements he thought should be satisfied in order to answer the question he posed of what is the best way of measuring uncertainty of certain possible outcomes. His theorem isnt neccessary for the theory; it mainly matches the definition plausible. The real justification comes from what the definition allows us to derive. This also makes me question whether those requirements were chosen becase Shannon considered them reasonable, and whether there is other better requirements or the legitimacy of his requirements.

Renyi then introduces a generalised extension of Shannon entropy providing us with a spectrum of entropy measures that quantify the diversity or uncertainty of a system based on a paramater a (alpha). Renyi measurements only mean something when probability distribution is uneven. Maybe I could implement Renyi entropy aswell to gain a deeper understanding of Shannon entropy or other further extensions of it to analyse the correctness of Shannon's work.