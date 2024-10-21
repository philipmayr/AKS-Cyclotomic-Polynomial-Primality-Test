// Agrawal–Kayal–Saxena (AKS) Cyclotomic Polynomial Primality Test 

#include <stdio.h>
#include <math.h>

int find_greatest_common_divisor(int a, int b)
{
    if (b == 0) return a;
    
    return find_greatest_common_divisor(b, a % b);
}

int exponentiate(int base, int index)
{
    int power = 1;
    
    if (index == 0) return power;
    if (index == 1) return base;
    
    while (index > 0)
    {
        if (index & 1) power *= base;
        
        base *= base;
        index >>= 1;
    }
    
    return power;    
}

int exponentiate_modularly(int base, int index, int modulus)
{
    int residue = 1;
    
    base %= modulus;
    
    if (base == 0) return 0;
    
    while (index > 0)
    {
        if (index & 1) residue = (residue * base) % modulus;
        
        base = (base * base) % modulus;
        index >>= 1;
    }
    
    return residue;    
}

int find_multiplicative_order(int modulus, int base)
{
    if (find_greatest_common_divisor(modulus, base) != 1) return -1;
    
    for (int order = 1; order < modulus; order++)
    {
        if (exponentiate_modularly(base, order, modulus) == 1) return order;
    } 
}

int test_perfect_exponentiality(int n)
{
    for (int k = 2; k <= n; k++)
    {
        for (int i = 2; i <= log2(n); i++)
        {
            int power = exponentiate(k, i);
            
            if (power > n) break;
            if (power == n) return 1;
        }
    }
    
    return 0;
}

int test_primality(int prime_candidate)
{
    if (prime_candidate < 2 || 
        !(prime_candidate & 1) ||
        test_perfect_exponentiality(prime_candidate) != 0)
    {
        return 0;
    }
    
    int binary_logarithm_of_prime_candidate = log2(prime_candidate);
    int square_of_binary_logarithm_of_prime_candidate = binary_logarithm_of_prime_candidate * binary_logarithm_of_prime_candidate;
    
    int base = 1;
    int multiplicative_order = find_multiplicative_order(base, prime_candidate);
    
    while (multiplicative_order < square_of_binary_logarithm_of_prime_candidate)
    {
        base++;
        multiplicative_order = find_multiplicative_order(base, prime_candidate);
    }
    
    if (find_greatest_common_divisor(base, prime_candidate) != 1) return 0;
    
    if (prime_candidate <= base) return 1;
    
    return 0;
}

int main(int argc, char *argv[])
{
    int prime_candidate;

    if (argc > 1)
    {
        for (int argument = 1; argument < argc; argument++)
        {
            prime_candidate = atoi(argv[argument]);
            
            if (test_primality(prime_candidate, 12)) printf("%d is a prime number.", prime_candidate);
            else printf("%d is not a prime number.", prime_candidate);

            printf("\n\n");
        }
    }
    
    for (;;)
    {    
        printf("Enter an integer to test for primality: ");
        
        // integer input validation
        // https://jackstromberg.com/2013/02/how-to-validate-numeric-integer-input-in-c/
        
        int input, status, temp;

    	  status = scanf("%d", &input);
    	
      	while(status != 1)
      	{
              while((temp = getchar()) != EOF && temp != '\n');
              
              printf("Invalid input.");
              printf("\n\n");
              printf("Enter an integer to test for primality: ");
              
              status = scanf("%d", &input);
      	}
    
    	  prime_candidate = input;
    	
    	  if (test_primality(prime_candidate)) printf("%d is a prime number.", prime_candidate);
        else printf("%d is not a prime number.", prime_candidate);
        
        printf("\n\n");
    }
    
    return 0;
}
