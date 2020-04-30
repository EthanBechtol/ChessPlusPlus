//
// Created by Ethan on 4/2/20.
//

#ifndef CHESSPLUSPLUS_PAIRHASH_HPP
#define CHESSPLUSPLUS_PAIRHASH_HPP

#include <utility>

template <class T1, class T2>
class PairHash {
public:
    size_t operator()(const std::pair<T1, T2>& p) const
    {
        auto first = std::hash<T1>{}(p.first);
        auto second = std::hash<T2>{}(p.second);

        return first ^ second;
    }
};

#endif //CHESSPLUSPLUS_PAIRHASH_HPP
