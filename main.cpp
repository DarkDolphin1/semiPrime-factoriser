#include<iostream>
#include<cstdlib>
#include<ctime>
#include<random>
#include<math.h>

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

    int genRandom (int& N){
        srand(N);
        return (rand() % (N)) + 1;
    }

    pair<int,int> findR (int &semiP){
        // int g = genRandom(semiP);
        int g = 8;
        int i = 1;
        int r = -1;
        while(true){
            long long expo = pow(g,i);
            if( (expo % semiP ) == 1){
                // r is preferred to be even , hence if i is odd , we multiply it by 2 as m doesn't matter and possible value of r are periodic 
                r = (i%2==0)? i:(i*2);
                break; 
            }
            i++;
            cout<<" expo is found to be "<< expo <<endl; // for debugging , r is being shown as 0 . 
        }
        cout<<" r is found to be "<<r<<endl; // for debugging , r is being shown as 0 .
        return {g,r} ;
    }

    int gcd (int a , int b){
        while(b!= 0){
            int temp = b;
            b = a % b;
            a = temp;
        }
    return a;
    }

    bool isCorrect (int p , int q , int N){
        return p*q == N;
    }

    bool isPrime(int n) {
    if (n <= 1) return false;
    if (n == 2 || n == 3) return true;  
    if (n % 2 == 0 || n % 3 == 0) return false; 
    for (int i = 5; i * i <= n; i = i + 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

    int core (int& N){
        auto Pair = findR(N);
        int g = Pair.first;
        int r = Pair.second;
        // int g = 8;
        // int r = 10;

        if( r == -1 ){
            cout<<"Error in core , could not find r "<<endl;
            return -1;
        } 

        int Z = pow(g,(r/2));
        int a = Z - 1;
        int b = Z + 1;

        // using Euclid's algorithm 
        int p = gcd(a,N);
        // p is one of the factors of N 
        int q = gcd(b,N);

        if(isCorrect(p,q,N)){
            cout<<"the factors of N are \n";
            cout<<" P = "<<p<<endl;
            cout<<" Q = "<<q<<endl;
            cout<<" Confirmimg the results "<<endl;
            cout<<" Running the primality check on p and q ..."<<endl;
            cout<<" p is prime "<< isPrime(p) <<endl;
            cout<<" q is prime "<< isPrime(q) <<endl;
            return 0;

        } else {
            cout<<" wrong answer , p * q is not equal to N "<<endl;
            cout<<" logging values \n";
            cout<<" p : "<<p<<" \n q : "<<q<<" \n N : "<<N;
            return -1;
        }
        return -1;
    }

    

int main (){
    int semiPrime;
    cout<<"Enter a semi prime number "<<endl;
    cin >> semiPrime;
    if(core(semiPrime) == -1){
        cout<<"Error in core , terminating program ";
    }
    return 0;
}