#include<iostream>
#include<ctime>
#include<math.h>
#include<gmp.h>
#include<gmpxx.h>
#include"utils.h"

using namespace std;

/*
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

    1. genRandom (calls none , uses <random>)
    2. findR (calls genRandome() , uses <math.h>)
    3. gcd (calls none)
    4. isCorrect (calls none)
    5. isPrime (calls none)
    6. core (calls findR() , isCorrect() , isPrime() , gcd() , uses <math.h>)
    7. main (calls core() , very sensative to core's return value)

TO FIX : 
 1 use a big number library to handle large values as expo , as even a 'long long int' is not enough .
 2 pow has a precision loss as it works with double and returns a double , casting is not safe either .
 3 hardcoded the value of g as to avoid overflows .
 4 g must not share factors with N , hence a safety check is required .
 
*/

/* PORTING NOTES
    1 mpz_t can't be returned safely , deal with it.
    2 GMP provides powm() , hence expo doesn't needs to be stored . 
        instead u = g^r % N.
    3 GMP provides its own gcd function , hence removed gcd().
    4 core will still return int values as these are to recognise the behaviour of core 
*/
    auto genRand (const mpz_class& upperBound){
    gmp_randstate_t state;
    gmp_randinit_default(state);

    mpz_class randNumber;

    mpz_class seed = time(NULL);
    
    gmp_randseed(state,seed.get_mpz_t());

    mpz_class N = upperBound;

    mpz_urandomm( randNumber.get_mpz_t() , state, N.get_mpz_t());

    gmp_randclear(state);

    return randNumber;
}

    pair<mpz_class,mpz_class> findR (mpz_class semiPrime){
        auto g = genRand(semiPrime);
        mpz_class i = 1;
        mpz_class r = -1;

        const mpz_class one = 1;
        
        while(true){
            mpz_class u; // u = (g^i) % N 
            mpz_powm(u.get_mpz_t() , g.get_mpz_t() ,i.get_mpz_t() ,semiPrime.get_mpz_t() );
            if( u == one ){  
                // r is preferred to be even , hence if i is odd , we multiply it by 2 as m doesn't matter and possible value of r are periodic 
                r = (i%2==0)? i:(i*2);
                break; 
            }
            i++;
        }
        return {g,r} ;
    }


    bool isCorrect (mpz_class p , mpz_class q , mpz_class N){
        return p*q == N;
    }

    bool isPrime(mpz_class n) {
    if(n <= 1) return false;
    if(n == 2 || n == 3) return true;
    if( (n%2) == 0 || (n%3) == 0) return false;

    for(int i = 5; i*i <=n; i = i + 6){
        if( n % i == 0 || n % (i+2) == 0) return false;
    }
    return true;
}

    int core ( mpz_class N){
        auto Pair = findR(N);
        mpz_class g = Pair.first;
        mpz_class r = Pair.second;
        
            if( r == -1 ){
                cout<<"Error in core , could not find r "<<endl;
                return -1;
            } 
        
        mpz_class halfR = r / 2;
        mpz_class Z;
        mpz_pow(Z.get_mpz_t(),g.get_mpz_t(),halfR.get_mpz_t());
        mpz_class a = Z - 1;
        mpz_class b = Z + 1;

        // using Euclid's algorithm 

        // p is one of the factors of N 
        // q is the other factor of N 

        mpz_class p = gcd(a,N);
        mpz_class q = gcd(b,N);

        logResults(p.get_mpz_t(),q.get_mpz_t(),g.get_mpz_t(),r.get_mpz_t(),N.get_mpz_t());

        std::cout<<"\n verify the results ?  [Y/n]"<<std::endl;
        char ans;
        std:cin>>ans;
        
        if(ans == 'Y'){
            switch ( confirmResults(p.get_mpz_t(),q.get_mpz_t(),N.get_mpz_t())){
            case 0:
                break;
            
            case 1:
                std::cout<<"\n \n error code 1 ";
                break;

            case 2:
                std::cout<<"\n \n error code 2 ";
                break;
            case 3:
                std::cout<<"\n \n error code 3 ";
                break;

            default:
                std::cout<<"\n \n undefined behaviour";
                break;
            };
        }
        return -1;
    }

    

int main (){
    mpz_class semiPrime;
    cout<<"Enter a semi prime number "<<endl;
    cin >> semiPrime;
    if(core(semiPrime) == -1){
        cout<<"Error in core , terminating program ";
    }
    return 0;
}