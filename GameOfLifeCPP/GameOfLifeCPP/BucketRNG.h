#pragma once
#include <vector>

class BucketRNG
{
public:
	BucketRNG(float(*f)(float), int numberOfBuckets);
	BucketRNG(float(*f)(float), int numberOFBuckets, int seed);
	~BucketRNG();
	float GetRandom01();
	float GetRandom(float min, float max);

protected:
	float(*weight)(float);
	bool ValidateFunction(float(*w)(float));
	void InitBuckets();
	float AddJitter(float initialValue);

	int numberOfBuckets;
	std::vector<int> buckets;
	std::vector<int> knownSums;
};
