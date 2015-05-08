#include <vector>

class BucketRNG
{
public:
	BucketRNG(float(*w)(float), int numberOfBuckets);
	BucketRNG(float(*w)(float), int numberOFBuckets, int seed);
	~BucketRNG();
	float GetRandom01();
	float GetRandom(float min, float max);

protected:
	float(*weight)(float);
	bool ValidateFunction(float(*w)(float));
	void InitBuckets();

	std::vector<float> buckets;
};
