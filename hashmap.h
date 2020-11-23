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
    ~HashMap() {
        //cout << "Warning! Memory leak! TODO: implement ~HashMap()\n";
        for (auto p : m_prtsToDelete) {
            delete p;
        }
    }
private:
    class TreeNode {
    private:
        pair<K, V> m_keyValue;
    public:
        TreeNode(const K& key_, const V& value_) : m_keyValue({key_, value_}) { }
        const K& key() {
            return m_keyValue.first;
        }
        V& value() {
            return m_keyValue.second;
        }
        TreeNode* left{nullptr};
        TreeNode* right{nullptr};
    };
    static constexpr size_t MAX_HASH = (2 << (sizeof(HashType) * 8 - 1));
    vector<TreeNode*> m_map = vector<TreeNode*>(MAX_HASH, nullptr);
    vector<TreeNode*> m_prtsToDelete;
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
    get(key_) = value_;
}

template<typename K, typename V>
V& HashMap<K, V>::get(const K& key_) {
    auto h = hash_functions::hash(key_);
    auto treeNode = m_map[h];
    //cout << "treeNode " << treeNode.get() << endl;
    TreeNode* previous = nullptr;
    while (treeNode != nullptr) {
        previous = treeNode;
        if (key_ == treeNode->key()) {
            //treeNode->value() = V();
            return treeNode->value();
        } else if (key_ > treeNode->key()) {
            treeNode = treeNode->right;
        } else {
            treeNode = treeNode->left;
        }
    }
    if (previous == nullptr) {
        m_map[h] = new TreeNode(key_, V());
        m_prtsToDelete.push_back(m_map[h]);
        return m_map[h]->value();
    } else {
        if (key_ > previous->key()) {
            previous->right = new TreeNode(key_, V());
            m_prtsToDelete.push_back(previous->right);
            return previous->right->value();
        } else {
            previous->left = new TreeNode(key_, V());
            m_prtsToDelete.push_back(previous->left);
            return previous->left->value();
        }
    }
}

#endif // HASHMAP_H
