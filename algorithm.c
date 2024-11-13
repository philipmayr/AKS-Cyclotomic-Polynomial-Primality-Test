// Agrawal–Kayal–Saxena (AKS) Cyclotomic Polynomial Primality Test 

#include <stdio.h>
#include <math.h>

int find_greatest_common_divisor(int a, int b)
{
    return b ? find_greatest_common_divisor(b, a % b) : a;
}

double find_square_root(double square)
{
    if (square < 1) return 0;
    
    double root = square / 3;
    
    for (int i = 0; i < sizeof (double) * 4; i++)
        root = (root + (square / root)) >> 1;
        
    return root;
}

int exponentiate(int base, int index)
{
    if (base == 0) return 0;
    if (index == 0) return 1;
    if (index == 1) return base;

    int power = 1;
    
    while (index)
    {
        if (index & 1) power *= base;
        
        base *= base;

        index >>= 1;
    }
    
    return power;    
}

int exponentiate_modularly(int base, int index, int modulus)
{
    if (base == 0) return 0;
    if (index == 0) return 1;

    if (base > modulus) base %= modulus;
    if (index == 1) return base;
    
    int residue = 1;
    
    while (index)
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
        if (exponentiate_modularly(base, order, modulus) == 1) return order;
}

int find_binary_logarithm(int power)
{
    int exponent = 0;

    while (power >>= 1) exponent++;

    // for (int i = sizeof (i) * 2; i > 0; i >>= 1) 
    //     if ((1 << (exponent + i)) <= power) exponent += i;

    return exponent;
}

int test_perfect_exponentiality(int number)
{
    for (int base = 2; base <= n; base++)
    {
        for (int index = 2; index <= find_binary_exponent(number); index++)
        {
            int power = exponentiate(base, index);
            
            if (power > number) break;
            else if (power == number) return 1;
        }
    }
    
    return 0;
}

int get_lesser_of_twain(int a, int b)
{
    return a < b ? a : b;
}

int find_totient(int number)
{
    int totient = 1;
    
    for (int coprime_candidate_iterator = 2; coprime_candidate_iterator < number; coprime_candidate_iterator++)
        if (find_greatest_common_divisor(coprime_candidate_iterator, number) == 1) totient++;
    
    return totient;
}

int test_primality(int prime_candidate)
{
    if (~prime_candidate & 1 || prime_candidate < 2 || test_perfect_exponentiality(prime_candidate)) return 0;
    
    float binary_logarithm_of_prime_candidate = log2(prime_candidate);
    float square_of_binary_logarithm_of_prime_candidate = binary_logarithm_of_prime_candidate * binary_logarithm_of_prime_candidate;
    
    int witness = 1;
    int multiplicative_order = find_multiplicative_order(witness, prime_candidate);
    
    while (multiplicative_order < square_of_binary_logarithm_of_prime_candidate)
    {
        witness++;
        multiplicative_order = find_multiplicative_order(witness, prime_candidate);
    }
    
    if (find_greatest_common_divisor(witness, prime_candidate) != 1) return 0;
    
    if (prime_candidate <= witness) return 1;
    
    int upper_bound = get_lesser_of_twain(witness, prime_candidate - 1);
    
    for (int a = 2; a < upper_bound; a++)
        if (prime_candidate % a) return 0;
    
    upper_bound = find_square_root(find_totient(witness)) * binary_logarithm_of_prime_candidate;
    
    for (int a = 1; a < upper_bound; a++)
    {
        // TODO
        
        return 0;
    }
    
    return 1;
}

int main()
{
    int prime_candidate;
    
    for (;;)
    {    
        printf("Enter an odd candidate integer to test for primality: ");
        
        // integer input validation
        // https://jackstromberg.com/2013/02/how-to-validate-numeric-integer-input-in-c/
        
        int input, status, buffer;

    	status = scanf("%d", & input);
    	
    	while (status != 1)
    	{
            while ((buffer = getchar()) != EOF && buffer != '\n');
            
            printf("Invalid input.");
            printf("\n\n");
            printf("Enter an odd candidate integer to test for primality: ");
            
            status = scanf("%d", & input);
    	}
    
    	prime_candidate = input;
    	
    	if (test_primality(prime_candidate)) printf("%d is a prime number.", prime_candidate);
        else printf("%d is not a prime number.", prime_candidate);
        
        printf("\n\n");
    }
    
    return 0;
}
