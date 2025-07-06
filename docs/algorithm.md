## 🧠 Algorithm

This project uses a mathematical trick to factor semi-primes...

the process starts with a semi Prime number N . 
here , N = p * q , where p and q are prime numbers.

 first we select a random number g

    we have a elegant mathematical proof of g^r = mN + 1.
    this ultimately says that any number g , if exponented enough (r) times , will always reach (a multiple of N ) + 1

    by this , we can conclude that g^r % N = 1.
    m is none of our buisness here , just r .

now we have r and g such that , g^r = mN + 1.

    simplifing the equation
        (g^r - 1) = mN
        (g^(r/2) - 1) (g^(r/2) + 1) = mN
        let (g^(r/2) - 1) = a
        let (g^(r/2) + 1) = b

    a and b likely share factors with N .


using Euclid's algorithm to find the GCD of a & N and b & N . 

    now we have p and q 
    check if N is product of p and q
    check if p and q are prime
    
    if both are true , the result is correct



## the sequence of function goes in such a way that , if one function calls another , the called function must be declared before (above) the caller function

    1. genRand
    2. findR 
    3. core 
    4. main (calls core() , very sensative to core's return value)