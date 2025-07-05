#include<iostream>
#include<gmp.h>
#include<gmpxx.h>

void mpz_pow( mpz_t result , const mpz_t base , const mpz_t exponent ){
    mpz_set_ui(result , 1);

    mpz_t exp , temp_base;

    mpz_init_set(exp,exponent);
    mpz_init_set(temp_base,base);

    while(mpz_cmp_ui(exp,0) > 0){
        if(mpz_odd_p(exp)){
            mpz_mul(result , result , temp_base);   // result = result * temp_base
        }
        mpz_mul(temp_base,temp_base,temp_base);     // squaring temp_base  
        mpz_fdiv_q_2exp(exp,exp,1);                 // dividing exponent by 2 
    }

    mpz_clear(exp);
    mpz_clear(temp_base);
}

    int confirmResults (const mpz_t p , const mpz_t q , const mpz_t N ){
        mpz_t result;
        mpz_mul(result , p , q );

        bool truth = (mpz_cmp(result , N) == 0);
        if(!truth){
            return 1;
        }
        int rep = 10;

        auto confidence = mpz_probab_prime_p(p,rep);

        TESTP:
        switch (confidence){
            case 0:
                std::cout<<"\n P is not prime \n";
                return 2;
            case 1:
                if(rep == 25)break;
                rep = 25;
                confidence = mpz_probab_prime_p(p, rep);
                goto TESTP;
                break;
            case 2:
                std::cout<<"P is prime , prime check completed";
                break;
            default:
                std::cout<<"Unexpected output from 'mpz_probab_prime_p' ";
                return 10;
                break;
        }

        rep = 10;
        confidence = mpz_probab_prime_p(q,rep);
        
        TESTQ:
        switch (confidence){
            case 0:
                std::cout<<"\n Q is not prime \n";
                return 3;
            case 1:
                if(rep == 25 ) break;
                rep = 25;
                confidence = mpz_probab_prime_p(p, rep);
                goto TESTP;
                break;
            
            case 2:
                std::cout<<"Q is prime , prime check completed";
                break;
            
            default:
                std::cout<<"Unexpected output from 'mpz_probab_prime_p' ";
                return 10;
                break;
        }
        return 0;

    }

    void logResults ( mpz_t p , mpz_t q , mpz_t g , mpz_t r , mpz_t N ){
        gmp_printf("\n value of P : %Zd\n", p);
        gmp_printf("\n value of Q : %Zd\n", q);
        gmp_printf("\n value of g : %Zd\n", g);
        gmp_printf("\n value of r : %Zd\n", r);
        gmp_printf("\n value of N : %Zd\n", N);
    }