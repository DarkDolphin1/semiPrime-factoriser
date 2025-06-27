# SemiPrime Cracker

This is a basic C++ implementation that attempts to factor a **semi-prime number** (a number made by multiplying two primes) using modular arithmetic and some fun crypto - math logic.

Built purely for learning purposes 



## How It Works

Given a semi-prime `N`(product of two primes p and q ), the program:

1. Picks a number `g`
2. Finds `r` such that `g^r ≡ 1 mod N`
3. Computes `g^(r/2) ± 1`
4. Uses Euclid’s algorithm to find `GCD`s → which gives the prime factors `p` and `q`
5. Validates that `p * q == N` and checks primality of both

---

## Limitations

- pow() returns a double , hence there is a precision loss while working with bigger numbers
- the mathematical operations used here are exponential and C++ can't handle these safely for large numbers 
- runs into integer overflow due to C++'s limitations , works upto 91 .  
- Meant for learning, not production-level factorization .
- No BigInt support (for now) .

---

## TODO 
- [ ] Integrate GNU Multiple Precision Arithmetic Library (GMP)
- [ ] Improve randomization logic for generating `g`
- [ ] Optimize for speed and memory usage


## 🛠️ Usage

```bash
g++ main.cpp -o cracker
./cracker
