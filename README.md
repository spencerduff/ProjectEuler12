# ProjectEuler12
Finds number of divisors of a number and solves ProjectEuler 12's problem

It first makes a triangle number starting at 5 and keeps going until it finds the first triangle number who has over 500 divisors.
The way it finds the triangle number (a summation from a number and all numbers preceding it) is by Gauss's formula:
Sum from 1->n = n(n+1)/2
After it has the triangle number, it fills a vector of PrimeFactors with a recursive function fillPrimeFactors. It takes an integer and
determines if it is prime or not. If it is, it puts it in the PrimeFactors vector and returns. If it isn't, it finds the first prime
factor of that number and divides it out, then adds that prime factor to the PrimeFactors vector, and calls fillPrimeFactors again on the
remaining number without the prime factor.
The way it finds the next prime is a function that takes a prime number and then finds the next prime after it by checking all proceeding
odd numbers if they're prime.
Once the recursive function returns, it checks how many factors the triangle number has by multiplying the frequency of the prime factors
plus one to each other. So for 54, it would have 3^3*2^1 as its prime factors. To find the total number of factors, the formula is
(3+1)*(1+1) = 8, where 3 is because we see a prime number (3) three times, and we see another prime number (2) one time.
54's factors: (1, 2, 3, 6, 9, 18, 27, 54).
After it finds the triangle number's number of factors, it checks if it's over 500 and if it isn't, will loop again after clearing the 
vector of prime factors. If it does, then the program prints out the triangle number and exits.

There is also code for making a prime sieve, but proved to be too slow, because we don't need to know all the primes to find the prime 
factorization of a number. It is quicker to just find primes as we need them.
