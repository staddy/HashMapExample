#ifndef HASHMAP_H
#define HASHMAP_H

#include <vector>
#include <string>

using namespace std;

using HashType = unsigned char;

template<typename K, typename V>
class HashMap {
public:
    void insert(const K& key_, const V& value_);
    V& get(const K& key_);
    V& operator[](const K& key_) {
        return get(key_);
    }
private:
    static constexpr size_t MAX_HASH = (2 << (sizeof(HashType) * 8 - 1));
    vector<vector<pair<K, V> > > m_map = vector<vector<pair<K, V> > >(MAX_HASH);
};

namespace hash_functions {

HashType hash(const string& key_) {
    HashType retVal{0};
    for (const auto c : key_) {
        retVal += c;
    }
    return retVal;
}

HashType hash(int key_) {
    return key_ % 256;
}

}

template<typename K, typename V>
void HashMap<K, V>::insert(const K& key_, const V& value_) {
    auto h = hash_functions::hash(key_);
    auto& subVector = m_map[h];
    for (auto& kv : subVector) {
        if (kv.first == key_) {
            kv.second = value_;
            return;
        }
    }
    subVector.push_back({key_, value_});
}

template<typename K, typename V>
V& HashMap<K, V>::get(const K& key_) {
    auto h = hash_functions::hash(key_);
    auto& subVector = m_map[h];
    for (auto& kv : subVector) {
        if (kv.first == key_) {
            return kv.second;
        }
    }
    subVector.push_back({key_, V()});
    return subVector.back().second;
}

#endif // HASHMAP_H
