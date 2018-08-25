#include "splayTree.h"
#include <stdexcept>


template<typename Key, typename Value>
class cacheLRU  : private SplayTree<Key, Value>
{
public:
	cacheLRU(int capacity);
	~cacheLRU();
	void put(const std::pair<const Key, Value>& keyValuePair);
	std::pair<const Key, Value> get(const Key& key);


private: 
	int current_capacity;
	int cache_capacity;
};


template<typename Key, typename Value>
cacheLRU<Key, Value>::cacheLRU(int capacity){
	cache_capacity = capacity;
	current_capacity = 0;

}


template<typename Key, typename Value>
cacheLRU<Key, Value>::~cacheLRU(){
}

template<typename Key, typename Value>
void cacheLRU<Key, Value>::put(const std::pair<const Key, Value>& keyValuePair){
	
	typename SplayTree<Key, Value>::iterator it;
	it = SplayTree<Key, Value>::find(keyValuePair.first);
	if(it == SplayTree<Key, Value>::end()){
		if(current_capacity < cache_capacity){
			SplayTree<Key, Value>::insert(keyValuePair);
			current_capacity++;
		}
		else{

			SplayTree<Key, Value>::deleteMinLeaf();
			SplayTree<Key, Value>::insert(keyValuePair);
		}
	}
}



template<typename Key, typename Value>
std::pair<const Key, Value> cacheLRU<Key, Value>::get(const Key& key){
	typename SplayTree<Key, Value>::iterator it;
	it = SplayTree<Key, Value>::find(key);

	if(it != SplayTree<Key, Value>::end()){
		return (*it);
	}
	else{
		
		throw std::logic_error("ERROR");
	}

}





