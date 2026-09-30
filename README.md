# Shannon Entropy - Programming Assignment 1

This project investigates the mathematical and computational correctness of Shannon entropy.It begins with a direct implementation of Shannon entropy for discrete probability distributions, including input validation, zero-probability handling, and tests based on known values and mathematical invariants. I then implement Rényi entropy as a generalisation of Shannon entropy to compare which properties are shared across entropy measures and which help distinguish Shannon entropy, including permutation invariance, maximum entropy for uniform distributions, independent additivity, and Shannon’s grouping/recursivity property. Finally, I investigate the limiting relationship \(H_\alpha \to H_1\) as \(\alpha \to 1\), identify numerical instability in a direct Rényi implementation, and implement a more numerically stable version using expm1 and log1p. Detailed investigation results and observations are recorded in docs/notes.md.

## Build and run

These commands were tested in Windows PowerShell using g++ 15.2.0 from MSYS2 MinGW64. You need g++ installed and available in your PATH. On my machine it is in `C:\msys64\mingw64\bin`. No extra libraries or testing frameworks are needed.

After cloning the repo, open a terminal in the `Advanced-Algorithms-Assignment-1` folder, which contains `src`, `tests` and this README. Run all the commands below from that folder.


## Tests

Compile and run the Shannon tests:

```powershell
g++ -std=c++17 tests/test_shannon_entropy.cpp src/shannon_entropy.cpp src/probability_distribution.cpp -o test_shannon_entropy.exe
.\test_shannon_entropy.exe
```

Compile and run the Renyi tests:

```powershell
g++ -std=c++17 tests/test_renyi_entropy.cpp src/renyi_entropy.cpp src/shannon_entropy.cpp src/probability_distribution.cpp -o test_renyi_entropy.exe
.\test_renyi_entropy.exe
```

Both test programs ran successfully with these commands. The Shannon tests print `All Shannon entropy tests passed.` The Renyi tests print `All Renyi entropy tests passed.` and then continue with the additivity and grouping experiments, so let the program finish aswell.

The tests use assertions, so a failed check stops the program. Keep assertions enabled when compiling, which the commands above do. The Renyi tests also print the comparison between the original and stable implementations as alpha approaches 1. These comparisons and the Renyi grouping results are printed for investigation rather than checked with assertions.

The executables are created in the repo folder. After changing any source or test files, run the relevant compile command again before running the executable.
