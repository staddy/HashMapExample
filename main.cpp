#include "hashmap.h"
#include "slowhashmap.h"

#include <QDateTime>
#include <iostream>
#include <unordered_map>

auto constexpr N = 100000;

int main(int argc, char* argv[]) {
    HashMap<int, int> fastMap;
    SlowHashMap<int, int> slowMap;
    unordered_map<int, int> superFastMap;
    auto t = QDateTime::currentMSecsSinceEpoch();
    for (size_t i = 0; i < N; ++i) {
        superFastMap[i] = i;
    }
    cout << "superFastMap: " << (QDateTime::currentMSecsSinceEpoch() - t) << endl;
    t = QDateTime::currentMSecsSinceEpoch();
    for (size_t i = 0; i < N; ++i) {
        fastMap.insert(i, i);
    }
    cout << (QDateTime::currentMSecsSinceEpoch() - t) << endl;
    t = QDateTime::currentMSecsSinceEpoch();
    for (size_t i = 0; i < N; ++i) {
        slowMap.insert(i, i);
    }
    cout << (QDateTime::currentMSecsSinceEpoch() - t) << endl;

    return 0;
}
