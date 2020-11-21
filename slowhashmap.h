#ifndef SLOWHASHMAP_H
#define SLOWHASHMAP_H

#include <vector>
#include <string>

using namespace std;

template<typename K, typename V>
class SlowHashMap {
public:
    void insert(const K& key_, const V& value_);
    V& get(const K& key_);
    V& operator[](const K& key_) {
        return get(key_);
    }
private:
    vector<K> m_keys;
    vector<V> m_values;
};

template<typename K, typename V>
void SlowHashMap<K, V>::insert(const K& key_, const V& value_) {
    for (auto it = m_keys.begin(); it != m_keys.end(); ++it) {
        if (*it == key_) {
            m_values[it - m_keys.begin()] = value_;
            return;
        }
    }
    m_keys.push_back(key_);
    m_values.push_back(value_);
}

template<typename K, typename V>
V& SlowHashMap<K, V>::get(const K& key_) {
    for (auto it = m_keys.begin(); it != m_keys.end(); ++it) {
        if (*it == key_) {
            return m_values[it - m_keys.begin()];
        }
    }
    m_keys.push_back(key_);
    m_values.push_back(V());
    return m_values.back();
}
#endif // SLOWHASHMAP_H
