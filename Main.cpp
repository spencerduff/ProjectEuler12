#include <iostream>
#include <math.h>
#include <vector>

struct PrimeFactor{
	int freq;
	unsigned long long prime;

	PrimeFactor(unsigned long long p){
		freq = 1;
		prime = p;
	}

	bool operator ==(const PrimeFactor &rhs) const { return prime == rhs.prime; }
};

struct PrimeFactorVec{
	std::vector<PrimeFactor> vec;

	PrimeFactorVec(){}

	void insert(unsigned long long p){
		auto a = std::find(vec.begin(), vec.end(), PrimeFactor(p));
		if (a == vec.end()){
			vec.push_back(PrimeFactor(p));
		}
		else {
			vec[a - vec.begin()].freq++;
		}
	}

};

void fillPrimeFactors(unsigned long long n);
bool isPerfectSquare(unsigned long long n);
void fillSieveBetween(unsigned long long n, unsigned long long m);
unsigned long long makeTriangleNumber(unsigned long long n);
bool isPrimeWithSieve(unsigned long long n);
int numOfFactors(PrimeFactorVec vec);
int findNextPrime(unsigned long long p);
bool isPrime(unsigned long long p);

std::vector<unsigned long long> primeSieve;
PrimeFactorVec currFactors;


int main(){
	primeSieve.push_back(2);
	unsigned long long sieveCounter = 5;
	int currMaxFactors = 0;
	for (; true; sieveCounter += 250){
		//fillSieveBetween(primeSieve.at(primeSieve.size() - 1), makeTriangleNumber(sieveCounter + 250) / 2 + 1);
		for (unsigned long long i = sieveCounter; i < sieveCounter + 250; i++){
			unsigned long long triNum = makeTriangleNumber(i);
			fillPrimeFactors(triNum);
			int num = numOfFactors(currFactors);
			if (num > currMaxFactors){
				currMaxFactors = num;
				std::cout << currMaxFactors << std::endl;
			}
			if (num >= 500){
				std::cout << "First TriNum with 500+ divisors: " << triNum << std::endl;
				return 0;
			}
			currFactors.vec.clear();
		}
	}

	return 0;
}

void fillPrimeFactors(unsigned long long n){

	if (isPrime(n))	{
		currFactors.insert(n);
		return;
	}
	unsigned long long primeFac = 2;
	while (n%primeFac != 0){
		primeFac = findNextPrime(primeFac);
	}

	currFactors.insert(primeFac);

	fillPrimeFactors(n / primeFac);
}

bool isPerfectSquare(unsigned long long n){
	return ((llround(sqrt(n))*llround(sqrt(n))) == n);
}

void fillSieveBetween(unsigned long long n, unsigned long long m){
	std::vector<unsigned long long> toCheck;
	unsigned long long i = n;
	if (i % 2 == 0)
		++i;
	for (; i < m; i += 2){
		toCheck.push_back(i);
	}
	bool subK = false;
	for (int k = 0; k < toCheck.size(); ++k){
		int temp = k;
		for (unsigned int j = 0; j < primeSieve.size(); ++j){
			if (primeSieve[j] * primeSieve[j] > toCheck[k])
				break;
			if (toCheck[k] % primeSieve[j] == 0){
				toCheck.erase(toCheck.begin() + k);
				k--;
				break;
			}
		}
		if (temp == k){
			primeSieve.push_back(toCheck[k]);
			toCheck.erase(toCheck.begin() + k);
			k--;
		}
	}
}

unsigned long long makeTriangleNumber(unsigned long long n){
	return (n*(n + 1)) / 2;
}

bool isPrimeWithSieve(unsigned long long n){
	auto a = std::find(primeSieve.begin(), primeSieve.end(), n);
	if (a == primeSieve.end())
		return false;
	return true;
}

int numOfFactors(PrimeFactorVec vec){
	int total = 1;
	for (unsigned int i = 0; i < vec.vec.size(); i++){
		total *= vec.vec[i].freq + 1;
	}
	return total;
}

int findNextPrime(unsigned long long p){
	if (p % 2 == 0)
		p++;
	else
		p += 2;
	while (!isPrime(p)){
		p += 2;
	}
	return p;
}

bool isPrime(unsigned long long p){
	if (p <= 1)
		return false;
	else if (p <= 3)
		return true;
	else if (p % 2 == 0 || p % 3 == 0)
		return false;
	unsigned long long i = 5;
	while (i*i <= p){
		if (p%i == 0 || p % (i + 2) == 0)
			return false;
		i += 6;
	}
	return true;
}
