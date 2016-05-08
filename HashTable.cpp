#include <iostream>

using namespace std;

template <class K, class V>
struct Pair
{
	K key;
	V value;
};

template <class K>
int hash_func(K)

template <class K, class V>
class HT
{
private:
	vector <vector <pair <K, V> > > table;
	//ensure
public:
	HT(int n, int (*hash_func)(const K&))
	{
		K* table = new K[n];
	}
	void put(const K&, const V&){}
	V& get(const K&){}
};

int main()
{

}