#include <functional>
#include <vector>
#include <list>
#include <utility>
#include <functional>

template <typename K, typename V>
class Unordered_map 
{
private:
	vector<list<pair<K,V>>> store;
	int bucketSize;
	float maxLoadFactor; //this can be internal
	//so basically, std:hash<T> is a function object that computer a size_t hash value
	int numOfElement; //indicate the number of element in the hashmap
	int getBucketIndex(const K& key) const
	{
		return std::hash<K>{}(key) % bucketSize; //value init after the type init
	}
public:
	Unordered_map(int initSize =8, float loadFactor = 0.75): bucketSize(initSize), maxLoadFactor(loadFactor), numOfElement(0)
	{
		store.resize(bucketSize);
	}

	void insert(const K& k, const V& v)
	{
		int idx= getBucketIndex(k);
		//there might be multiple element
		//check if the given key exist
		for(auto& kv: store[idx])
		{
			if(kv.first == k)
			{
				kv.second  = value;
				return ;
			}
		}
		store[idx].push_back({k,v});
		numOfElement++;
		float currLoadFac = static_cast<float>(numOfElement)/ bucketSize;
		if(currLoadFac >= maxLoadFactor)
		{
			rehash(bucketSize*2);
		}
	}


	bool find(const K& k, V& val)
	{
		int idx= getBucketIndex(k);
		for(auto& kv: store[idx])
		{
			if(kv.first == k)
			{
				val = kv.second;
				return  true;
			}
		}

		return false;
	}

	void rehash(int newBucketSize)
	{
		vector <list<pair<K,V>>> newStore(newBucketSize);
		for(auto & bucket: store)
		{
			for(auto& kv: store[bucket])
			{
				//recalculate the hash
				int newIdx=  std::hash<K>{}(kv.first) % newBucketSize;
				newStore[newIdx].push_back(kv);
			}
		}
		store.swap(newStore);
		bucketSize= newBucketSize;
	}


};
