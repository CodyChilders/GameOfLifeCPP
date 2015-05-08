#include <vector>
#include <ctime>
#include <cstdlib>
#include <exception>

#include "BucketRNG.h"

#define samples 100.0

using namespace std;

BucketRNG::BucketRNG(float(*f)(float), int numberOfBuckets)
{
	if (!ValidateFunction(f))
	{
		throw new exception("Invalid function passed to BucketRNG::BucketRNG(float(*f), int)");
	}
	srand(time(NULL));
	weight = f;
	InitBuckets();
}

BucketRNG::BucketRNG(float(*f)(float), int numberOFBuckets, int seed)
{
	if (!ValidateFunction(f))
	{
		throw new exception("Invalid function passed to BucketRNG::BucketRNG(float(*f), int, int)");
	}
	srand(seed);
	weight = f;
	InitBuckets();
}

BucketRNG::~BucketRNG()
{
	buckets.clear();
	knownSums.clear();
}

float BucketRNG::GetRandom01()
{
	printf("BucketRNG.GetRandom01 not implemented\n");
	return 0;
}

float BucketRNG::GetRandom(float min, float max)
{
	printf("BucketRNG.GetRandom not implemented\n");
	return 0;
}

//This function returns true if the given function will be acceptable 
bool BucketRNG::ValidateFunction(float(*w)(float))
{
	//sample it through the range to make sure it won't break the algorithm
	for (double i = 0; i <= 1; i += 1.0 / samples)
	{

	}
	return true;
}

void BucketRNG::InitBuckets()
{

}

float BucketRNG::AddJitter(float initialValue)
{
	printf("BucketRNG.AddJitter not implemente\n");
	return 0;
}

