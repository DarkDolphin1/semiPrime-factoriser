#include<iostream>
#include<ctime>
#include<gmp.h>
#include<gmpxx.h>
#include"utils.h"

using namespace std;


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
                // r is preferred to be even  
                r = (i%2==0)? i:(i*2);
                break; 
            }
            i++;
        }
        return {g,r} ;
    }


    int core ( mpz_class N){
        auto Pair = findR(N);
        mpz_class g = Pair.first;
        mpz_class r = Pair.second;
        
            if( r == -1 ){
                cout<<" Error in core , could not find r "<<endl;
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


        std::cout<<" verify the results ?  [Y/n] \n"<<std::endl;
        char ans;
        std:cin>>ans;
        
        if(ans == 'Y'){
            switch ( confirmResults(p,q,N) ){
            case 0:
                break;
            
            case 1:
                std::cout<<"\n error code 1 \n";
                break;

            case 2:
                std::cout<<"\n error code 2 \n";
                break;
            case 3:
                std::cout<<"\n error code 3 \n";
                break;

            default:
                std::cout<<"\n undefined behaviour \n ";
                break;
            };
        }
        return 0;
    }

int main (){
    mpz_class semiPrime;
    cout<<" Enter a semi prime number"<<endl;
    cin >> semiPrime;
    if(core(semiPrime) == -1){
        cout<<" Error in core , terminating program \n";
    }
    return 0;
}